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
struct enc_softc {int dummy; } ;
struct cam_periph {scalar_t__ softc; } ;

/* Variables and functions */
 int cam_periph_error (union ccb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cam_periph* xpt_path_periph (int /*<<< orphan*/ ) ; 

int
enc_error(union ccb *ccb, uint32_t cflags, uint32_t sflags)
{
	struct enc_softc *softc;
	struct cam_periph *periph;

	periph = xpt_path_periph(ccb->ccb_h.path);
	softc = (struct enc_softc *)periph->softc;

	return (cam_periph_error(ccb, cflags, sflags));
}