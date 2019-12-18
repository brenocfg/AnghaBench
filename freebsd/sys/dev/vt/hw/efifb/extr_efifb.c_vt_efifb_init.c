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
struct vt_device {struct fb_info* vd_softc; } ;
struct fb_info {int fb_height; int fb_bpp; int fb_stride; int fb_size; intptr_t fb_vbase; int /*<<< orphan*/  fb_pbase; int /*<<< orphan*/  fb_cmap; int /*<<< orphan*/  fb_depth; int /*<<< orphan*/  fb_width; } ;
struct efi_fb {int fb_height; int fb_mask_red; int fb_mask_green; int fb_mask_blue; int fb_mask_reserved; int fb_stride; int /*<<< orphan*/  fb_addr; int /*<<< orphan*/  fb_width; } ;
typedef  int /*<<< orphan*/ * caddr_t ;

/* Variables and functions */
 int CN_DEAD ; 
 int CN_INTERNAL ; 
 int /*<<< orphan*/  COLOR_FORMAT_RGB ; 
 int MODINFOMD_EFI_FB ; 
 int MODINFO_METADATA ; 
 int NBBY ; 
 int /*<<< orphan*/  VM_MEMATTR_WRITE_COMBINING ; 
 scalar_t__ ffs (int) ; 
 int /*<<< orphan*/  fls (int) ; 
 int /*<<< orphan*/  local_info ; 
 scalar_t__ pmap_mapdev_attr (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * preload_search_by_type (char*) ; 
 scalar_t__ preload_search_info (int /*<<< orphan*/ *,int) ; 
 int roundup2 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vt_fb_init (struct vt_device*) ; 
 int /*<<< orphan*/  vt_generate_cons_palette (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,int,scalar_t__,int,scalar_t__) ; 

__attribute__((used)) static int
vt_efifb_init(struct vt_device *vd)
{
	struct fb_info	*info;
	struct efi_fb	*efifb;
	caddr_t		kmdp;

	info = vd->vd_softc;
	if (info == NULL)
		info = vd->vd_softc = (void *)&local_info;

	kmdp = preload_search_by_type("elf kernel");
	if (kmdp == NULL)
		kmdp = preload_search_by_type("elf64 kernel");
	efifb = (struct efi_fb *)preload_search_info(kmdp,
	    MODINFO_METADATA | MODINFOMD_EFI_FB);
	if (efifb == NULL)
		return (CN_DEAD);

	info->fb_height = efifb->fb_height;
	info->fb_width = efifb->fb_width;

	info->fb_depth = fls(efifb->fb_mask_red | efifb->fb_mask_green |
	    efifb->fb_mask_blue | efifb->fb_mask_reserved);
	/* Round to a multiple of the bits in a byte. */
	info->fb_bpp = roundup2(info->fb_depth, NBBY);

	/* Stride in bytes, not pixels */
	info->fb_stride = efifb->fb_stride * (info->fb_bpp / NBBY);

	vt_generate_cons_palette(info->fb_cmap, COLOR_FORMAT_RGB,
	    efifb->fb_mask_red, ffs(efifb->fb_mask_red) - 1,
	    efifb->fb_mask_green, ffs(efifb->fb_mask_green) - 1,
	    efifb->fb_mask_blue, ffs(efifb->fb_mask_blue) - 1);

	info->fb_size = info->fb_height * info->fb_stride;
	info->fb_pbase = efifb->fb_addr;
	info->fb_vbase = (intptr_t)pmap_mapdev_attr(info->fb_pbase,
	    info->fb_size, VM_MEMATTR_WRITE_COMBINING);

	vt_fb_init(vd);

	return (CN_INTERNAL);
}