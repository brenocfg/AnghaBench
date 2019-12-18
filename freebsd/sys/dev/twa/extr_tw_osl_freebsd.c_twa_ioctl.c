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
struct twa_softc {int /*<<< orphan*/  ctlr_handle; } ;
struct thread {int dummy; } ;
struct cdev {scalar_t__ si_drv1; } ;
typedef  scalar_t__ caddr_t ;
typedef  int /*<<< orphan*/  TW_INT8 ;
typedef  int /*<<< orphan*/  TW_INT32 ;

/* Variables and functions */
#define  TW_OSL_IOCTL_FIRMWARE_PASS_THROUGH 129 
#define  TW_OSL_IOCTL_SCAN_BUS 128 
 int /*<<< orphan*/  tw_cl_ioctl (int /*<<< orphan*/ *,int,scalar_t__) ; 
 int /*<<< orphan*/  tw_osli_dbg_dprintf (int,struct twa_softc*,char*,...) ; 
 int /*<<< orphan*/  tw_osli_fw_passthru (struct twa_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tw_osli_request_bus_scan (struct twa_softc*) ; 

__attribute__((used)) static TW_INT32
twa_ioctl(struct cdev *dev, u_long cmd, caddr_t buf, TW_INT32 flags, struct thread *proc)
{
	struct twa_softc	*sc = (struct twa_softc *)(dev->si_drv1);
	TW_INT32		error;

	tw_osli_dbg_dprintf(5, sc, "entered");

	switch (cmd) {
	case TW_OSL_IOCTL_FIRMWARE_PASS_THROUGH:
		tw_osli_dbg_dprintf(6, sc, "ioctl: fw_passthru");
		error = tw_osli_fw_passthru(sc, (TW_INT8 *)buf);
		break;

	case TW_OSL_IOCTL_SCAN_BUS:
		/* Request CAM for a bus scan. */
		tw_osli_dbg_dprintf(6, sc, "ioctl: scan bus");
		error = tw_osli_request_bus_scan(sc);
		break;

	default:
		tw_osli_dbg_dprintf(6, sc, "ioctl: 0x%lx", cmd);
		error = tw_cl_ioctl(&sc->ctlr_handle, cmd, buf);
		break;
	}
	return(error);
}