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
typedef  scalar_t__ u_int ;
typedef  int /*<<< orphan*/  term_color_t ;
struct vt_device {struct vga_softc* vd_softc; } ;
struct vga_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEM_WRITE1 (struct vga_softc*,scalar_t__,int) ; 
 scalar_t__ VT_VGA_MEMSIZE ; 
 int /*<<< orphan*/  vga_setfg (struct vt_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vga_blank(struct vt_device *vd, term_color_t color)
{
	struct vga_softc *sc = vd->vd_softc;
	u_int ofs;

	vga_setfg(vd, color);
	for (ofs = 0; ofs < VT_VGA_MEMSIZE; ofs++)
		MEM_WRITE1(sc, ofs, 0xff);
}