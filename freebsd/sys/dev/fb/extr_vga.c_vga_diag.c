#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ vi_mode; } ;
typedef  TYPE_1__ video_info_t ;
struct TYPE_15__ {int va_flags; int va_initial_mode; scalar_t__ va_type; int va_unit; char* va_name; } ;
typedef  TYPE_2__ video_adapter_t ;
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_13__ {int /*<<< orphan*/ * regs; } ;
struct TYPE_12__ {int /*<<< orphan*/ * regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIOS_PADDRTOVADDR (int) ; 
 int ENXIO ; 
 scalar_t__ EOT ; 
 scalar_t__ KD_EGA ; 
 scalar_t__ KD_VGA ; 
 scalar_t__ NA ; 
 int /*<<< orphan*/  RTC_EQUIPMENT ; 
 int /*<<< orphan*/  VGA_DRIVER_NAME ; 
 int V_ADP_MODECHANGE ; 
 int V_MODE_PARAM_SIZE ; 
 TYPE_11__ adpstate ; 
 TYPE_10__ adpstate2 ; 
 TYPE_1__* bios_vmode ; 
 int /*<<< orphan*/  dump_buffer (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fb_dump_adp_info (int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int /*<<< orphan*/  fb_dump_mode_info (int /*<<< orphan*/ ,TYPE_2__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/ * get_mode_param (scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int readb (int /*<<< orphan*/ ) ; 
 int readw (int /*<<< orphan*/ ) ; 
 int rows_offset ; 
 int rtcin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vga_get_info (TYPE_2__*,int,TYPE_1__*) ; 
 int /*<<< orphan*/  vga_init_done ; 
 int /*<<< orphan*/ * video_mode_ptr ; 
 int video_mode_ptr2 ; 

__attribute__((used)) static int
vga_diag(video_adapter_t *adp, int level)
{
    u_char *mp;
#if FB_DEBUG > 1
    video_info_t info;
    int i;
#endif

    if (!vga_init_done)
	return ENXIO;

#if FB_DEBUG > 1
#ifndef VGA_NO_BIOS
    printf("vga: RTC equip. code:0x%02x, DCC code:0x%02x\n",
	   rtcin(RTC_EQUIPMENT), readb(BIOS_PADDRTOVADDR(0x488)));
    printf("vga: CRTC:0x%x, video option:0x%02x, ",
	   readw(BIOS_PADDRTOVADDR(0x463)),
	   readb(BIOS_PADDRTOVADDR(0x487)));
    printf("rows:%d, cols:%d, font height:%d\n",
	   readb(BIOS_PADDRTOVADDR(0x44a)),
	   readb(BIOS_PADDRTOVADDR(0x484)) + 1,
	   readb(BIOS_PADDRTOVADDR(0x485)));
#endif /* VGA_NO_BIOS */
#if !defined(VGA_NO_BIOS) && !defined(VGA_NO_MODE_CHANGE)
    printf("vga: param table EGA/VGA:%p", video_mode_ptr);
    printf(", CGA/MDA:%p\n", video_mode_ptr2);
    printf("vga: rows_offset:%d\n", rows_offset);
#endif
#endif /* FB_DEBUG > 1 */

    fb_dump_adp_info(VGA_DRIVER_NAME, adp, level);

#if FB_DEBUG > 1
    if (adp->va_flags & V_ADP_MODECHANGE) {
	for (i = 0; bios_vmode[i].vi_mode != EOT; ++i) {
	    if (bios_vmode[i].vi_mode == NA)
		continue;
	    if (get_mode_param(bios_vmode[i].vi_mode) == NULL)
		continue;
	    fb_dump_mode_info(VGA_DRIVER_NAME, adp, &bios_vmode[i], level);
	}
    } else {
	vga_get_info(adp, adp->va_initial_mode, &info);	/* shouldn't fail */
	fb_dump_mode_info(VGA_DRIVER_NAME, adp, &info, level);
    }
#endif /* FB_DEBUG > 1 */

    if ((adp->va_type != KD_EGA) && (adp->va_type != KD_VGA))
	return 0;
#if !defined(VGA_NO_BIOS) && !defined(VGA_NO_MODE_CHANGE)
    if (video_mode_ptr == NULL)
	printf("vga%d: %s: WARNING: video mode switching is not "
	       "fully supported on this adapter\n",
	       adp->va_unit, adp->va_name);
#endif
    if (level <= 0)
	return 0;

    if (adp->va_type == KD_VGA) {
	printf("VGA parameters upon power-up\n");
	dump_buffer(adpstate.regs, sizeof(adpstate.regs));
	printf("VGA parameters in BIOS for mode %d\n", adp->va_initial_mode);
	dump_buffer(adpstate2.regs, sizeof(adpstate2.regs));
    }

    mp = get_mode_param(adp->va_initial_mode);
    if (mp == NULL)	/* this shouldn't be happening */
	return 0;
    printf("EGA/VGA parameters to be used for mode %d\n", adp->va_initial_mode);
    dump_buffer(mp, V_MODE_PARAM_SIZE);

    return 0;
}