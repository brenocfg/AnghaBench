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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  size_t term_color_t ;
struct vt_device {struct creatorfb_softc* vd_softc; } ;
struct TYPE_2__ {int fb_height; int fb_stride; int /*<<< orphan*/  fb_width; int /*<<< orphan*/ * fb_cmap; } ;
struct creatorfb_softc {TYPE_1__ fb; int /*<<< orphan*/  memh; int /*<<< orphan*/  memt; } ;

/* Variables and functions */
 int /*<<< orphan*/  bus_space_set_region_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
creatorfb_blank(struct vt_device *vd, term_color_t color)
{
	struct creatorfb_softc *sc;
	uint32_t c;
	int i;

	sc = vd->vd_softc;
	c = sc->fb.fb_cmap[color];

	for (i = 0; i < sc->fb.fb_height; i++)
		bus_space_set_region_4(sc->memt, sc->memh, i*sc->fb.fb_stride,
		    c, sc->fb.fb_width);
}