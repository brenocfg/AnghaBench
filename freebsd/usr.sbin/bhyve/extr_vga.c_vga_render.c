#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_5__ {int atc_mode; } ;
struct TYPE_4__ {scalar_t__ gc_misc_gm; } ;
struct vga_softc {TYPE_2__ vga_atc; TYPE_1__ vga_gc; TYPE_3__* gc_image; } ;
struct bhyvegc {int dummy; } ;
struct TYPE_6__ {int width; int height; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int ATC_MC_GA ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vga_check_size (struct bhyvegc*,struct vga_softc*) ; 
 scalar_t__ vga_in_reset (struct vga_softc*) ; 
 int /*<<< orphan*/  vga_render_graphics (struct vga_softc*) ; 
 int /*<<< orphan*/  vga_render_text (struct vga_softc*) ; 

void
vga_render(struct bhyvegc *gc, void *arg)
{
	struct vga_softc *sc = arg;

	vga_check_size(gc, sc);

	if (vga_in_reset(sc)) {
		memset(sc->gc_image->data, 0,
		    sc->gc_image->width * sc->gc_image->height *
		     sizeof (uint32_t));
		return;
	}

	if (sc->vga_gc.gc_misc_gm && (sc->vga_atc.atc_mode & ATC_MC_GA))
		vga_render_graphics(sc);
	else
		vga_render_text(sc);
}