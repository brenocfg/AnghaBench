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
struct vt_device {int vd_flags; int vd_width; int vd_height; int /*<<< orphan*/ * vd_video_dev; struct vga_softc* vd_softc; } ;
struct vga_softc {int vga_enabled; int /*<<< orphan*/  vga_fb_handle; int /*<<< orphan*/  vga_fb_tag; int /*<<< orphan*/  vga_reg_handle; int /*<<< orphan*/  vga_reg_tag; } ;

/* Variables and functions */
 int CN_DEAD ; 
 int CN_INTERNAL ; 
 int /*<<< orphan*/  TUNABLE_INT_FETCH (char*,int*) ; 
 int VDF_DOWNGRADE ; 
 int VDF_TEXTMODE ; 
 int /*<<< orphan*/  VGA_MEM_BASE ; 
 int /*<<< orphan*/  VGA_MEM_SIZE ; 
 int /*<<< orphan*/  VGA_REG_BASE ; 
 int /*<<< orphan*/  VGA_REG_SIZE ; 
 int /*<<< orphan*/  VGA_TXT_BASE ; 
 int /*<<< orphan*/  VGA_TXT_SIZE ; 
 scalar_t__ VM_GUEST_NO ; 
 int VT_VGA_HEIGHT ; 
 int VT_VGA_WIDTH ; 
 int /*<<< orphan*/  X86_BUS_SPACE_IO ; 
 int /*<<< orphan*/  X86_BUS_SPACE_MEM ; 
 int /*<<< orphan*/  bus_space_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vga_conssoftc ; 
 scalar_t__ vga_initialize (struct vt_device*,int) ; 
 int /*<<< orphan*/  vga_pci_repost (int /*<<< orphan*/ *) ; 
 scalar_t__ vm_guest ; 

__attribute__((used)) static int
vga_init(struct vt_device *vd)
{
	struct vga_softc *sc;
	int textmode;

	if (vd->vd_softc == NULL)
		vd->vd_softc = (void *)&vga_conssoftc;
	sc = vd->vd_softc;

	if (vd->vd_flags & VDF_DOWNGRADE && vd->vd_video_dev != NULL)
		vga_pci_repost(vd->vd_video_dev);

#if defined(__amd64__) || defined(__i386__)
	sc->vga_fb_tag = X86_BUS_SPACE_MEM;
	sc->vga_reg_tag = X86_BUS_SPACE_IO;
#else
# error "Architecture not yet supported!"
#endif

	bus_space_map(sc->vga_reg_tag, VGA_REG_BASE, VGA_REG_SIZE, 0,
	    &sc->vga_reg_handle);

	/*
	 * If "hw.vga.textmode" is not set and we're running on hypervisor,
	 * we use text mode by default, this is because when we're on
	 * hypervisor, vt(4) is usually much slower in graphics mode than
	 * in text mode, especially when we're on Hyper-V.
	 */
	textmode = vm_guest != VM_GUEST_NO;
	TUNABLE_INT_FETCH("hw.vga.textmode", &textmode);
	if (textmode) {
		vd->vd_flags |= VDF_TEXTMODE;
		vd->vd_width = 80;
		vd->vd_height = 25;
		bus_space_map(sc->vga_fb_tag, VGA_TXT_BASE, VGA_TXT_SIZE, 0,
		    &sc->vga_fb_handle);
	} else {
		vd->vd_width = VT_VGA_WIDTH;
		vd->vd_height = VT_VGA_HEIGHT;
		bus_space_map(sc->vga_fb_tag, VGA_MEM_BASE, VGA_MEM_SIZE, 0,
		    &sc->vga_fb_handle);
	}
	if (vga_initialize(vd, textmode) != 0)
		return (CN_DEAD);
	sc->vga_enabled = true;

	return (CN_INTERNAL);
}