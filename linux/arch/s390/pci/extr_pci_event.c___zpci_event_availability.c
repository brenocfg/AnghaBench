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
struct zpci_dev {void* state; int /*<<< orphan*/  fh; int /*<<< orphan*/  fid; int /*<<< orphan*/  bus; } ;
struct zpci_ccdf_avail {int /*<<< orphan*/  fid; int /*<<< orphan*/  fh; int /*<<< orphan*/  pec; } ;
struct pci_dev {int /*<<< orphan*/  error_state; } ;
typedef  enum zpci_state { ____Placeholder_zpci_state } zpci_state ;

/* Variables and functions */
 int /*<<< orphan*/  ZPCI_DEVFN ; 
 void* ZPCI_FN_STATE_CONFIGURED ; 
 int ZPCI_FN_STATE_RESERVED ; 
 void* ZPCI_FN_STATE_STANDBY ; 
 int clp_add_pci_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clp_get_state (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  clp_rescan_pci_devices () ; 
 struct zpci_dev* get_zdev_by_fid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_channel_io_perm_failure ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 struct pci_dev* pci_get_slot (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_lock_rescan_remove () ; 
 char* pci_name (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_rescan_bus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_stop_and_remove_bus_device_locked (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_unlock_rescan_remove () ; 
 int /*<<< orphan*/  pr_info (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sclp_pci_deconfigure (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zpci_dbg (int,char*,int /*<<< orphan*/ ,int) ; 
 int zpci_disable_device (struct zpci_dev*) ; 
 int zpci_enable_device (struct zpci_dev*) ; 
 int /*<<< orphan*/  zpci_err (char*) ; 
 int /*<<< orphan*/  zpci_err_hex (struct zpci_ccdf_avail*,int) ; 
 int /*<<< orphan*/  zpci_remove_device (struct zpci_dev*) ; 

__attribute__((used)) static void __zpci_event_availability(struct zpci_ccdf_avail *ccdf)
{
	struct zpci_dev *zdev = get_zdev_by_fid(ccdf->fid);
	struct pci_dev *pdev = NULL;
	enum zpci_state state;
	int ret;

	if (zdev)
		pdev = pci_get_slot(zdev->bus, ZPCI_DEVFN);

	pr_info("%s: Event 0x%x reconfigured PCI function 0x%x\n",
		pdev ? pci_name(pdev) : "n/a", ccdf->pec, ccdf->fid);
	zpci_err("avail CCDF:\n");
	zpci_err_hex(ccdf, sizeof(*ccdf));

	switch (ccdf->pec) {
	case 0x0301: /* Reserved|Standby -> Configured */
		if (!zdev) {
			ret = clp_add_pci_device(ccdf->fid, ccdf->fh, 0);
			if (ret)
				break;
			zdev = get_zdev_by_fid(ccdf->fid);
		}
		if (!zdev || zdev->state != ZPCI_FN_STATE_STANDBY)
			break;
		zdev->state = ZPCI_FN_STATE_CONFIGURED;
		zdev->fh = ccdf->fh;
		ret = zpci_enable_device(zdev);
		if (ret)
			break;
		pci_lock_rescan_remove();
		pci_rescan_bus(zdev->bus);
		pci_unlock_rescan_remove();
		break;
	case 0x0302: /* Reserved -> Standby */
		if (!zdev)
			clp_add_pci_device(ccdf->fid, ccdf->fh, 0);
		break;
	case 0x0303: /* Deconfiguration requested */
		if (!zdev)
			break;
		if (pdev)
			pci_stop_and_remove_bus_device_locked(pdev);

		ret = zpci_disable_device(zdev);
		if (ret)
			break;

		ret = sclp_pci_deconfigure(zdev->fid);
		zpci_dbg(3, "deconf fid:%x, rc:%d\n", zdev->fid, ret);
		if (!ret)
			zdev->state = ZPCI_FN_STATE_STANDBY;

		break;
	case 0x0304: /* Configured -> Standby|Reserved */
		if (!zdev)
			break;
		if (pdev) {
			/* Give the driver a hint that the function is
			 * already unusable. */
			pdev->error_state = pci_channel_io_perm_failure;
			pci_stop_and_remove_bus_device_locked(pdev);
		}

		zdev->fh = ccdf->fh;
		zpci_disable_device(zdev);
		zdev->state = ZPCI_FN_STATE_STANDBY;
		if (!clp_get_state(ccdf->fid, &state) &&
		    state == ZPCI_FN_STATE_RESERVED) {
			zpci_remove_device(zdev);
		}
		break;
	case 0x0306: /* 0x308 or 0x302 for multiple devices */
		clp_rescan_pci_devices();
		break;
	case 0x0308: /* Standby -> Reserved */
		if (!zdev)
			break;
		zpci_remove_device(zdev);
		break;
	default:
		break;
	}
	pci_dev_put(pdev);
}