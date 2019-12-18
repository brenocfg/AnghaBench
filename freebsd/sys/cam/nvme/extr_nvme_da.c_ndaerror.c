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
struct TYPE_2__ {int status; int /*<<< orphan*/  path; } ;
union ccb {TYPE_1__ ccb_h; } ;
typedef  int /*<<< orphan*/  u_int32_t ;
struct nda_softc {int /*<<< orphan*/  errors; int /*<<< orphan*/  timeouts; } ;
struct cam_periph {scalar_t__ softc; } ;

/* Variables and functions */
#define  CAM_ATA_STATUS_ERROR 134 
#define  CAM_CMD_TIMEOUT 133 
#define  CAM_DATA_RUN_ERR 132 
#define  CAM_REQ_ABORTED 131 
#define  CAM_REQ_CMP_ERR 130 
#define  CAM_REQ_TERMIO 129 
 int CAM_STATUS_MASK ; 
#define  CAM_UNREC_HBA_ERROR 128 
 int cam_periph_error (union ccb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cam_periph* xpt_path_periph (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ndaerror(union ccb *ccb, u_int32_t cam_flags, u_int32_t sense_flags)
{
	struct nda_softc *softc;
	struct cam_periph *periph;

	periph = xpt_path_periph(ccb->ccb_h.path);
	softc = (struct nda_softc *)periph->softc;

	switch (ccb->ccb_h.status & CAM_STATUS_MASK) {
	case CAM_CMD_TIMEOUT:
#ifdef CAM_IO_STATS
		softc->timeouts++;
#endif
		break;
	case CAM_REQ_ABORTED:
	case CAM_REQ_CMP_ERR:
	case CAM_REQ_TERMIO:
	case CAM_UNREC_HBA_ERROR:
	case CAM_DATA_RUN_ERR:
	case CAM_ATA_STATUS_ERROR:
#ifdef CAM_IO_STATS
		softc->errors++;
#endif
		break;
	default:
		break;
	}

	return(cam_periph_error(ccb, cam_flags, sense_flags));
}