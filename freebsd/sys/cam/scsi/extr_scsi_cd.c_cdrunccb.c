#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  path; } ;
union ccb {TYPE_1__ ccb_h; } ;
typedef  int /*<<< orphan*/  u_int32_t ;
struct cd_softc {TYPE_2__* disk; } ;
struct cam_periph {scalar_t__ softc; } ;
struct TYPE_4__ {int /*<<< orphan*/  d_devstat; } ;

/* Variables and functions */
 int cam_periph_runccb (union ccb*,int (*) (union ccb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ),int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cam_periph* xpt_path_periph (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cdrunccb(union ccb *ccb, int (*error_routine)(union ccb *ccb,
					      u_int32_t cam_flags,
					      u_int32_t sense_flags),
	 u_int32_t cam_flags, u_int32_t sense_flags)
{
	struct cd_softc *softc;
	struct cam_periph *periph;
	int error;

	periph = xpt_path_periph(ccb->ccb_h.path);
	softc = (struct cd_softc *)periph->softc;

	error = cam_periph_runccb(ccb, error_routine, cam_flags, sense_flags,
				  softc->disk->d_devstat);

	return(error);
}