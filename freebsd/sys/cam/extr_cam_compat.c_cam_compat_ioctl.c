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
struct cdev {int dummy; } ;
struct ccb_hdr_0x17 {int flags; } ;
typedef  int /*<<< orphan*/  d_ioctl_t ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int CAMGETPASSTHRU ; 
#define  CAMGETPASSTHRU_0x16 133 
#define  CAMGETPASSTHRU_0x17 132 
#define  CAMGETPASSTHRU_0x18 131 
 int CAMIOCOMMAND ; 
#define  CAMIOCOMMAND_0x16 130 
#define  CAMIOCOMMAND_0x17 129 
#define  CAMIOCOMMAND_0x18 128 
 int CAM_DATA_PADDR ; 
 int CAM_DATA_PHYS_0x16 ; 
 int CAM_DATA_SG ; 
 int CAM_DATA_SG_PADDR ; 
 int CAM_SCATTER_VALID_0x16 ; 
 int CAM_SG_LIST_PHYS_0x16 ; 
 int ENOTTY ; 
 int cam_compat_handle_0x17 (struct cdev*,int,scalar_t__,int,struct thread*,int /*<<< orphan*/ *) ; 
 int cam_compat_handle_0x18 (struct cdev*,int,scalar_t__,int,struct thread*,int /*<<< orphan*/ *) ; 

int
cam_compat_ioctl(struct cdev *dev, u_long cmd, caddr_t addr, int flag,
    struct thread *td, d_ioctl_t *cbfnp)
{
	int error;

	switch (cmd) {
	case CAMIOCOMMAND_0x16:
	{
		struct ccb_hdr_0x17 *hdr17;

		hdr17 = (struct ccb_hdr_0x17 *)addr;
		if (hdr17->flags & CAM_SG_LIST_PHYS_0x16) {
			hdr17->flags &= ~CAM_SG_LIST_PHYS_0x16;
			hdr17->flags |= CAM_DATA_SG_PADDR;
		}
		if (hdr17->flags & CAM_DATA_PHYS_0x16) {
			hdr17->flags &= ~CAM_DATA_PHYS_0x16;
			hdr17->flags |= CAM_DATA_PADDR;
		}
		if (hdr17->flags & CAM_SCATTER_VALID_0x16) {
			hdr17->flags &= CAM_SCATTER_VALID_0x16;
			hdr17->flags |= CAM_DATA_SG;
		}
		cmd = CAMIOCOMMAND;
		error = cam_compat_handle_0x17(dev, cmd, addr, flag, td, cbfnp);
		break;
	}
	case CAMGETPASSTHRU_0x16:
		cmd = CAMGETPASSTHRU;
		error = cam_compat_handle_0x17(dev, cmd, addr, flag, td, cbfnp);
		break;
	case CAMIOCOMMAND_0x17:
		cmd = CAMIOCOMMAND;
		error = cam_compat_handle_0x17(dev, cmd, addr, flag, td, cbfnp);
		break;
	case CAMGETPASSTHRU_0x17:
		cmd = CAMGETPASSTHRU;
		error = cam_compat_handle_0x17(dev, cmd, addr, flag, td, cbfnp);
		break;
	case CAMIOCOMMAND_0x18:
		cmd = CAMIOCOMMAND;
		error = cam_compat_handle_0x18(dev, cmd, addr, flag, td, cbfnp);
		break;
	case CAMGETPASSTHRU_0x18:
		cmd = CAMGETPASSTHRU;
		error = cam_compat_handle_0x18(dev, cmd, addr, flag, td, cbfnp);
		break;
	default:
		error = ENOTTY;
	}

	return (error);
}