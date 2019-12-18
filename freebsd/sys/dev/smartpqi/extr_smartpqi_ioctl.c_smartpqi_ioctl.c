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
typedef  int u_long ;
struct thread {int dummy; } ;
struct pqisrc_softstate {int dummy; } ;
struct cdev {struct pqisrc_softstate* si_drv1; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
#define  CCISS_GETDRIVVER 132 
#define  CCISS_GETPCIINFO 131 
#define  CCISS_PASSTHRU 130 
#define  CCISS_REGNEWD 129 
 int /*<<< orphan*/  DBG_ERR (char*) ; 
 int /*<<< orphan*/  DBG_FUNC (char*,int,...) ; 
 int /*<<< orphan*/  DBG_WARN (char*,int) ; 
 int ENOTTY ; 
 int PQI_STATUS_SUCCESS ; 
#define  SMARTPQI_PASS_THRU 128 
 scalar_t__ pqisrc_ctrl_offline (struct pqisrc_softstate*) ; 
 int pqisrc_passthru_ioctl (struct pqisrc_softstate*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pqisrc_scan_devices (struct pqisrc_softstate*) ; 
 int /*<<< orphan*/  smartpqi_get_driver_info_ioctl (int /*<<< orphan*/ ,struct cdev*) ; 
 int /*<<< orphan*/  smartpqi_get_pci_info_ioctl (int /*<<< orphan*/ ,struct cdev*) ; 

__attribute__((used)) static int smartpqi_ioctl(struct cdev *cdev, u_long cmd, caddr_t udata,
		int flags, struct thread *td)
{
	int error = PQI_STATUS_SUCCESS;
	struct pqisrc_softstate *softs = cdev->si_drv1;

	DBG_FUNC("IN cmd = 0x%lx udata = %p cdev = %p\n", cmd, udata, cdev);

	if (!udata) {
		DBG_ERR("udata is null !!\n");
	}

	if (pqisrc_ctrl_offline(softs)){
		DBG_ERR("Controller s offline !!\n");
		return ENOTTY;
	}

	switch (cmd) {
		case CCISS_GETDRIVVER:
			smartpqi_get_driver_info_ioctl(udata, cdev);
			break;
		case CCISS_GETPCIINFO:
			smartpqi_get_pci_info_ioctl(udata, cdev);
			break;
		case SMARTPQI_PASS_THRU:
		case CCISS_PASSTHRU:
			error = pqisrc_passthru_ioctl(softs, udata, 0);
			error = PQI_STATUS_SUCCESS;
			break;
		case CCISS_REGNEWD:
			error = pqisrc_scan_devices(softs);
			break;
		default:
			DBG_WARN( "!IOCTL cmd 0x%lx not supported", cmd);
			error = ENOTTY;
			break;
	}

	DBG_FUNC("OUT error = %d\n", error);
	return error;
}