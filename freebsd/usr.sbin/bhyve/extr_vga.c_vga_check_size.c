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
struct TYPE_6__ {int crtc_horiz_disp_end; int crtc_vert_disp_end; int crtc_overflow; } ;
struct TYPE_5__ {int seq_cm_dots; } ;
struct vga_softc {int gc_width; int gc_height; TYPE_3__ vga_crtc; TYPE_2__ vga_seq; TYPE_1__* gc_image; } ;
struct bhyvegc {int dummy; } ;
struct TYPE_4__ {int width; int height; } ;

/* Variables and functions */
 int CRTC_OF_VDE8 ; 
 int CRTC_OF_VDE8_SHIFT ; 
 int CRTC_OF_VDE9 ; 
 int CRTC_OF_VDE9_SHIFT ; 
 int /*<<< orphan*/  bhyvegc_resize (struct bhyvegc*,int,int) ; 
 scalar_t__ vga_in_reset (struct vga_softc*) ; 

__attribute__((used)) static void
vga_check_size(struct bhyvegc *gc, struct vga_softc *sc)
{
	int old_width, old_height;

	if (vga_in_reset(sc))
		return;

	//old_width = sc->gc_width;
	//old_height = sc->gc_height;
	old_width = sc->gc_image->width;
	old_height = sc->gc_image->height;

	/*
	 * Horizontal Display End: For text modes this is the number
	 * of characters.  For graphics modes this is the number of
	 * pixels per scanlines divided by the number of pixels per
	 * character clock.
	 */
	sc->gc_width = (sc->vga_crtc.crtc_horiz_disp_end + 1) *
	    sc->vga_seq.seq_cm_dots;

	sc->gc_height = (sc->vga_crtc.crtc_vert_disp_end |
	    (((sc->vga_crtc.crtc_overflow & CRTC_OF_VDE8) >> CRTC_OF_VDE8_SHIFT) << 8) |
	    (((sc->vga_crtc.crtc_overflow & CRTC_OF_VDE9) >> CRTC_OF_VDE9_SHIFT) << 9)) + 1;

	if (old_width != sc->gc_width || old_height != sc->gc_height)
		bhyvegc_resize(gc, sc->gc_width, sc->gc_height);
}