#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int bus_addr_t ;
struct TYPE_2__ {int board_type; } ;

/* Variables and functions */
 int CVMX_ADDR_DID (int /*<<< orphan*/ ) ; 
#define  CVMX_BOARD_TYPE_CUST_LANNER_MR955 131 
 int /*<<< orphan*/  CVMX_FULL_DID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CVMX_OCT_DID_PCI ; 
 int CVMX_OCT_PCI_IO_BASE ; 
 int CVMX_OCT_PCI_IO_SIZE ; 
 int CVMX_OCT_PCI_MEM1_BASE ; 
 int CVMX_OCT_PCI_MEM1_SIZE ; 
 int /*<<< orphan*/  CVMX_OCT_SUBDID_PCI_MEM1 ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int PCIB_BCR_PERR_ENABLE ; 
 int PCIB_BCR_SECBUS_RESET ; 
 int PCIB_BCR_SERR_ENABLE ; 
 int PCIC_BRIDGE ; 
 int /*<<< orphan*/  PCIM_BAR_MEM_BASE ; 
 int PCIM_CMD_BUSMASTEREN ; 
 int PCIM_CMD_MEMEN ; 
 int PCIM_CMD_PORTEN ; 
 int PCIM_HDRTYPE ; 
#define  PCIM_HDRTYPE_BRIDGE 130 
#define  PCIM_HDRTYPE_CARDBUS 129 
#define  PCIM_HDRTYPE_NORMAL 128 
 int /*<<< orphan*/  PCIR_BAR (int) ; 
 int /*<<< orphan*/  PCIR_BRIDGECTL_1 ; 
 int /*<<< orphan*/  PCIR_CACHELNSZ ; 
 int /*<<< orphan*/  PCIR_CLASS ; 
 int /*<<< orphan*/  PCIR_COMMAND ; 
 int /*<<< orphan*/  PCIR_HDRTYPE ; 
 int /*<<< orphan*/  PCIR_IOBASEH_1 ; 
 int /*<<< orphan*/  PCIR_IOBASEL_1 ; 
 int /*<<< orphan*/  PCIR_IOLIMITH_1 ; 
 int /*<<< orphan*/  PCIR_IOLIMITL_1 ; 
 int /*<<< orphan*/  PCIR_LATTIMER ; 
 int /*<<< orphan*/  PCIR_MEMBASE_1 ; 
 int /*<<< orphan*/  PCIR_MEMLIMIT_1 ; 
 int /*<<< orphan*/  PCIR_PRIBUS_1 ; 
 int /*<<< orphan*/  PCIR_SECBUS_1 ; 
 int /*<<< orphan*/  PCIR_SUBBUS_1 ; 
 int /*<<< orphan*/  PCIR_SUBCLASS ; 
 int PCIS_BRIDGE_PCI ; 
 int /*<<< orphan*/  cvmx_read64_uint32 (int) ; 
 TYPE_1__* cvmx_sysinfo_get () ; 
 int /*<<< orphan*/  cvmx_write64_uint32 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,unsigned int,unsigned int,unsigned int,int) ; 
 int /*<<< orphan*/  htole32 (int) ; 
 int le32toh (int /*<<< orphan*/ ) ; 
 unsigned int octopci_init_bar (int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int,unsigned int,int*) ; 
 unsigned int octopci_init_bus (int /*<<< orphan*/ ,unsigned int) ; 
 int octopci_read_config (int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  octopci_write_config (int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int,int /*<<< orphan*/ ,unsigned int,int) ; 

__attribute__((used)) static unsigned
octopci_init_device(device_t dev, unsigned b, unsigned s, unsigned f, unsigned secbus)
{
	unsigned barnum, bars;
	uint8_t brctl;
	uint8_t class, subclass;
	uint8_t command;
	uint8_t hdrtype;

	/* Read header type (again.)  */
	hdrtype = octopci_read_config(dev, b, s, f, PCIR_HDRTYPE, 1);

	/*
	 * Disable memory and I/O while programming BARs.
	 */
	command = octopci_read_config(dev, b, s, f, PCIR_COMMAND, 1);
	command &= ~(PCIM_CMD_MEMEN | PCIM_CMD_PORTEN);
	octopci_write_config(dev, b, s, f, PCIR_COMMAND, command, 1);

	DELAY(10000);

	/* Program BARs.  */
	switch (hdrtype & PCIM_HDRTYPE) {
	case PCIM_HDRTYPE_NORMAL:
		bars = 6;
		break;
	case PCIM_HDRTYPE_BRIDGE:
		bars = 2;
		break;
	case PCIM_HDRTYPE_CARDBUS:
		bars = 0;
		break;
	default:
		device_printf(dev, "%02x.%02x:%02x: invalid header type %#x\n",
		    b, s, f, hdrtype);
		return (secbus);
	}

	barnum = 0;
	while (barnum < bars)
		barnum = octopci_init_bar(dev, b, s, f, barnum, &command);

	/* Enable bus mastering.  */
	command |= PCIM_CMD_BUSMASTEREN;

	/* Enable whatever facilities the BARs require.  */
	octopci_write_config(dev, b, s, f, PCIR_COMMAND, command, 1);

	DELAY(10000);

	/* 
	 * Set cache line size.  On Octeon it should be 128 bytes,
	 * but according to Linux some Intel bridges have trouble
	 * with values over 64 bytes, so use 64 bytes.
	 */
	octopci_write_config(dev, b, s, f, PCIR_CACHELNSZ, 16, 1);

	/* Set latency timer.  */
	octopci_write_config(dev, b, s, f, PCIR_LATTIMER, 48, 1);

	/* Board-specific or device-specific fixups and workarounds.  */
	switch (cvmx_sysinfo_get()->board_type) {
#if defined(OCTEON_VENDOR_LANNER)
	case CVMX_BOARD_TYPE_CUST_LANNER_MR955:
		if (b == 1 && s == 7 && f == 0) {
			bus_addr_t busaddr, unitbusaddr;
			uint32_t bar;
			uint32_t tmp;
			unsigned unit;

			/*
			 * Set Tx DMA power.
			 */
			bar = octopci_read_config(dev, b, s, f,
			    PCIR_BAR(3), 4);
			busaddr = CVMX_ADDR_DID(CVMX_FULL_DID(CVMX_OCT_DID_PCI,
			    CVMX_OCT_SUBDID_PCI_MEM1));
			busaddr += (bar & (uint32_t)PCIM_BAR_MEM_BASE);
			for (unit = 0; unit < 4; unit++) {
				unitbusaddr = busaddr + 0x430 + (unit << 8);
				tmp = le32toh(cvmx_read64_uint32(unitbusaddr));
				tmp &= ~0x700;
				tmp |= 0x300;
				cvmx_write64_uint32(unitbusaddr, htole32(tmp));
			}
		}
		break;
#endif
	default:
		break;
	}

	/* Configure PCI-PCI bridges.  */
	class = octopci_read_config(dev, b, s, f, PCIR_CLASS, 1);
	if (class != PCIC_BRIDGE)
		return (secbus);

	subclass = octopci_read_config(dev, b, s, f, PCIR_SUBCLASS, 1);
	if (subclass != PCIS_BRIDGE_PCI)
		return (secbus);

	/* Enable memory and I/O access.  */
	command |= PCIM_CMD_MEMEN | PCIM_CMD_PORTEN;
	octopci_write_config(dev, b, s, f, PCIR_COMMAND, command, 1);

	/* Enable errors and parity checking.  Do a bus reset.  */
	brctl = octopci_read_config(dev, b, s, f, PCIR_BRIDGECTL_1, 1);
	brctl |= PCIB_BCR_PERR_ENABLE | PCIB_BCR_SERR_ENABLE;

	/* Perform a secondary bus reset.  */
	brctl |= PCIB_BCR_SECBUS_RESET;
	octopci_write_config(dev, b, s, f, PCIR_BRIDGECTL_1, brctl, 1);
	DELAY(100000);
	brctl &= ~PCIB_BCR_SECBUS_RESET;
	octopci_write_config(dev, b, s, f, PCIR_BRIDGECTL_1, brctl, 1);

	secbus++;

	/* Program memory and I/O ranges.  */
	octopci_write_config(dev, b, s, f, PCIR_MEMBASE_1,
	    CVMX_OCT_PCI_MEM1_BASE >> 16, 2);
	octopci_write_config(dev, b, s, f, PCIR_MEMLIMIT_1,
	    (CVMX_OCT_PCI_MEM1_BASE + CVMX_OCT_PCI_MEM1_SIZE - 1) >> 16, 2);

	octopci_write_config(dev, b, s, f, PCIR_IOBASEL_1,
	    CVMX_OCT_PCI_IO_BASE >> 8, 1);
	octopci_write_config(dev, b, s, f, PCIR_IOBASEH_1,
	    CVMX_OCT_PCI_IO_BASE >> 16, 2);

	octopci_write_config(dev, b, s, f, PCIR_IOLIMITL_1,
	    (CVMX_OCT_PCI_IO_BASE + CVMX_OCT_PCI_IO_SIZE - 1) >> 8, 1);
	octopci_write_config(dev, b, s, f, PCIR_IOLIMITH_1,
	    (CVMX_OCT_PCI_IO_BASE + CVMX_OCT_PCI_IO_SIZE - 1) >> 16, 2);

	/* Program prefetchable memory decoder.  */
	/* XXX */

	/* Probe secondary/subordinate buses.  */
	octopci_write_config(dev, b, s, f, PCIR_PRIBUS_1, b, 1);
	octopci_write_config(dev, b, s, f, PCIR_SECBUS_1, secbus, 1);
	octopci_write_config(dev, b, s, f, PCIR_SUBBUS_1, 0xff, 1);

	/* Perform a secondary bus reset.  */
	brctl |= PCIB_BCR_SECBUS_RESET;
	octopci_write_config(dev, b, s, f, PCIR_BRIDGECTL_1, brctl, 1);
	DELAY(100000);
	brctl &= ~PCIB_BCR_SECBUS_RESET;
	octopci_write_config(dev, b, s, f, PCIR_BRIDGECTL_1, brctl, 1);

	/* Give the bus time to settle now before reading configspace.  */
	DELAY(100000);

	secbus = octopci_init_bus(dev, secbus);

	octopci_write_config(dev, b, s, f, PCIR_SUBBUS_1, secbus, 1);

	return (secbus);
}