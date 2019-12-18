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
struct TYPE_2__ {int /*<<< orphan*/  path; } ;
union ccb {TYPE_1__ ccb_h; } ;
typedef  int /*<<< orphan*/  uint32_t ;
struct sg_softc {int dummy; } ;
struct cam_periph {scalar_t__ softc; } ;

/* Variables and functions */
 int cam_periph_error (union ccb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cam_periph* xpt_path_periph (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sgerror(union ccb *ccb, uint32_t cam_flags, uint32_t sense_flags)
{
	struct cam_periph *periph;
	struct sg_softc *softc;

	periph = xpt_path_periph(ccb->ccb_h.path);
	softc = (struct sg_softc *)periph->softc;

	return (cam_periph_error(ccb, cam_flags, sense_flags));
}