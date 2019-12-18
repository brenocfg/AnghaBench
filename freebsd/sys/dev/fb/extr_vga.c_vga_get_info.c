#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int vi_mode; int vi_buffer_size; int vi_window_size; int vi_planes; } ;
typedef  TYPE_1__ video_info_t ;
struct TYPE_7__ {int va_flags; int va_initial_mode; int /*<<< orphan*/  va_type; } ;
typedef  TYPE_2__ video_adapter_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
 int EOT ; 
 int NA ; 
 int V_ADP_COLOR ; 
 int V_ADP_MODECHANGE ; 
 TYPE_1__* bios_vmode ; 
 int /*<<< orphan*/ * get_mode_param (int) ; 
 int map_gen_mode_num (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  vga_init_done ; 

__attribute__((used)) static int
vga_get_info(video_adapter_t *adp, int mode, video_info_t *info)
{
    int i;

    if (!vga_init_done)
	return ENXIO;

    mode = map_gen_mode_num(adp->va_type, adp->va_flags & V_ADP_COLOR, mode);
#ifndef VGA_NO_MODE_CHANGE
    if (adp->va_flags & V_ADP_MODECHANGE) {
	/*
	 * If the parameter table entry for this mode is not found, 
	 * the mode is not supported...
	 */
	if (get_mode_param(mode) == NULL)
	    return EINVAL;
    } else
#endif /* VGA_NO_MODE_CHANGE */
    {
	/* 
	 * Even if we don't support video mode switching on this adapter,
	 * the information on the initial (thus current) video mode 
	 * should be made available.
	 */
	if (mode != adp->va_initial_mode)
	    return EINVAL;
    }

    for (i = 0; bios_vmode[i].vi_mode != EOT; ++i) {
	if (bios_vmode[i].vi_mode == NA)
	    continue;
	if (mode == bios_vmode[i].vi_mode) {
	    *info = bios_vmode[i];
	    /* XXX */
	    info->vi_buffer_size = info->vi_window_size*info->vi_planes;
	    return 0;
	}
    }
    return EINVAL;
}