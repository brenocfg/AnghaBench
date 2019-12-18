#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  unsigned long long uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct octeon_device {int rx_pause; int tx_pause; int /*<<< orphan*/  status; int /*<<< orphan*/ * droq; int /*<<< orphan*/ * watchdog_task; int /*<<< orphan*/  device; int /*<<< orphan*/  msix_on; int /*<<< orphan*/  rx_budget; int /*<<< orphan*/  tx_budget; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  LIO_CN23XX_SLI_SCRATCH1 ; 
 int /*<<< orphan*/  LIO_DEFAULT_RX_PKTS_PROCESS_BUDGET ; 
 int /*<<< orphan*/  LIO_DEFAULT_TX_PKTS_PROCESS_BUDGET ; 
 scalar_t__ LIO_DEV_CORE_OK ; 
 int /*<<< orphan*/  LIO_FLAG_MSIX_ENABLED ; 
 int LIO_NIC_STARTER_TIMEOUT ; 
 scalar_t__ LIO_STARTER_POLL_INTERVAL_MS ; 
 scalar_t__ atomic_load_acq_int (int /*<<< orphan*/ *) ; 
 scalar_t__ cold ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kproc_create (int /*<<< orphan*/ ,struct octeon_device*,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kproc_resume (int /*<<< orphan*/ *) ; 
 struct octeon_device* lio_allocate_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lio_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lio_dev_dbg (struct octeon_device*,char*) ; 
 int /*<<< orphan*/  lio_dev_err (struct octeon_device*,char*) ; 
 int /*<<< orphan*/  lio_dev_info (struct octeon_device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ lio_device_init (struct octeon_device*) ; 
 int /*<<< orphan*/  lio_droq_bh (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lio_mdelay (scalar_t__) ; 
 int lio_nic_starter (struct octeon_device*) ; 
 unsigned long long lio_read_csr64 (struct octeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lio_watchdog ; 
 int /*<<< orphan*/  lio_write_csr64 (struct octeon_device*,int /*<<< orphan*/ ,unsigned long long) ; 
 int /*<<< orphan*/  pci_get_bus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_function (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_slot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_vendor (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lio_attach(device_t device)
{
	struct octeon_device	*oct_dev = NULL;
	uint64_t	scratch1;
	uint32_t	error;
	int		timeout, ret = 1;
	uint8_t		bus, dev, function;

	oct_dev = lio_allocate_device(device);
	if (oct_dev == NULL) {
		device_printf(device, "Error: Unable to allocate device\n");
		return (-ENOMEM);
	}

	oct_dev->tx_budget = LIO_DEFAULT_TX_PKTS_PROCESS_BUDGET;
	oct_dev->rx_budget = LIO_DEFAULT_RX_PKTS_PROCESS_BUDGET;
	oct_dev->msix_on = LIO_FLAG_MSIX_ENABLED;

	oct_dev->device = device;
	bus = pci_get_bus(device);
	dev = pci_get_slot(device);
	function = pci_get_function(device);

	lio_dev_info(oct_dev, "Initializing device %x:%x %02x:%02x.%01x\n",
		     pci_get_vendor(device), pci_get_device(device), bus, dev,
		     function);

	if (lio_device_init(oct_dev)) {
		lio_dev_err(oct_dev, "Failed to init device\n");
		lio_detach(device);
		return (-ENOMEM);
	}

	scratch1 = lio_read_csr64(oct_dev, LIO_CN23XX_SLI_SCRATCH1);
	if (!(scratch1 & 4ULL)) {
		/*
		 * Bit 2 of SLI_SCRATCH_1 is a flag that indicates that
		 * the lio watchdog kernel thread is running for this
		 * NIC.  Each NIC gets one watchdog kernel thread.
		 */
		scratch1 |= 4ULL;
		lio_write_csr64(oct_dev, LIO_CN23XX_SLI_SCRATCH1, scratch1);

		error = kproc_create(lio_watchdog, oct_dev,
				     &oct_dev->watchdog_task, 0, 0,
				     "liowd/%02hhx:%02hhx.%hhx", bus,
				     dev, function);
		if (!error) {
			kproc_resume(oct_dev->watchdog_task);
		} else {
			oct_dev->watchdog_task = NULL;
			lio_dev_err(oct_dev,
				    "failed to create kernel_thread\n");
			lio_detach(device);
			return (-1);
		}
	}
	oct_dev->rx_pause = 1;
	oct_dev->tx_pause = 1;

	timeout = 0;
	while (timeout < LIO_NIC_STARTER_TIMEOUT) {
		lio_mdelay(LIO_STARTER_POLL_INTERVAL_MS);
		timeout += LIO_STARTER_POLL_INTERVAL_MS;

		/*
		 * During the boot process interrupts are not available.
		 * So polling for first control message from FW.
		 */
		if (cold)
			lio_droq_bh(oct_dev->droq[0], 0);

		if (atomic_load_acq_int(&oct_dev->status) == LIO_DEV_CORE_OK) {
			ret = lio_nic_starter(oct_dev);
			break;
		}
	}

	if (ret) {
		lio_dev_err(oct_dev, "Firmware failed to start\n");
		lio_detach(device);
		return (-EIO);
	}

	lio_dev_dbg(oct_dev, "Device is ready\n");

	return (0);
}