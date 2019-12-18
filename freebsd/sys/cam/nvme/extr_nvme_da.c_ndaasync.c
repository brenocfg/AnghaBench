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
typedef  int u_int32_t ;
struct nda_softc {int /*<<< orphan*/  disk; } ;
struct ccb_getdev {int /*<<< orphan*/  protocol; } ;
struct cam_periph {struct nda_softc* softc; } ;
struct cam_path {int dummy; } ;
typedef  int cam_status ;

/* Variables and functions */
#define  AC_ADVINFO_CHANGED 130 
#define  AC_FOUND_DEVICE 129 
#define  AC_LOST_DEVICE 128 
 int /*<<< orphan*/  CAM_PERIPH_BIO ; 
 int CAM_REQ_CMP ; 
 int CAM_REQ_INPROG ; 
 uintptr_t CDAI_TYPE_PHYS_PATH ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  PROTO_NVME ; 
 int cam_periph_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct cam_path*,void (*) (void*,int,struct cam_path*,void*),int const,struct ccb_getdev*) ; 
 int /*<<< orphan*/  cam_periph_async (struct cam_periph*,int,struct cam_path*,void*) ; 
 int /*<<< orphan*/  disk_attr_changed (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ndacleanup ; 
 int /*<<< orphan*/  ndaoninvalidate ; 
 int /*<<< orphan*/  ndaregister ; 
 int /*<<< orphan*/  ndastart ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static void
ndaasync(void *callback_arg, u_int32_t code,
	struct cam_path *path, void *arg)
{
	struct cam_periph *periph;

	periph = (struct cam_periph *)callback_arg;
	switch (code) {
	case AC_FOUND_DEVICE:
	{
		struct ccb_getdev *cgd;
		cam_status status;
 
		cgd = (struct ccb_getdev *)arg;
		if (cgd == NULL)
			break;

		if (cgd->protocol != PROTO_NVME)
			break;

		/*
		 * Allocate a peripheral instance for
		 * this device and start the probe
		 * process.
		 */
		status = cam_periph_alloc(ndaregister, ndaoninvalidate,
					  ndacleanup, ndastart,
					  "nda", CAM_PERIPH_BIO,
					  path, ndaasync,
					  AC_FOUND_DEVICE, cgd);

		if (status != CAM_REQ_CMP
		 && status != CAM_REQ_INPROG)
			printf("ndaasync: Unable to attach to new device "
				"due to status 0x%x\n", status);
		break;
	}
	case AC_ADVINFO_CHANGED:
	{
		uintptr_t buftype;

		buftype = (uintptr_t)arg;
		if (buftype == CDAI_TYPE_PHYS_PATH) {
			struct nda_softc *softc;

			softc = periph->softc;
			disk_attr_changed(softc->disk, "GEOM::physpath",
					  M_NOWAIT);
		}
		break;
	}
	case AC_LOST_DEVICE:
	default:
		cam_periph_async(periph, code, path, arg);
		break;
	}
}