#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ vi_width; scalar_t__ vi_height; scalar_t__ vi_cwidth; scalar_t__ vi_cheight; scalar_t__ vi_depth; scalar_t__ vi_planes; scalar_t__ vi_flags; } ;
typedef  TYPE_1__ video_info_t ;
typedef  int /*<<< orphan*/  video_adapter_t ;
struct TYPE_6__ {scalar_t__ vi_mode; scalar_t__ vi_width; scalar_t__ vi_height; scalar_t__ vi_cwidth; scalar_t__ vi_cheight; scalar_t__ vi_depth; scalar_t__ vi_planes; scalar_t__ vi_flags; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENXIO ; 
 scalar_t__ EOT ; 
 scalar_t__ NA ; 
 TYPE_4__* bios_vmode ; 
 scalar_t__ vga_get_info (int /*<<< orphan*/ *,scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  vga_init_done ; 

__attribute__((used)) static int
vga_query_mode(video_adapter_t *adp, video_info_t *info)
{
    int i;

    if (!vga_init_done)
	return ENXIO;

    for (i = 0; bios_vmode[i].vi_mode != EOT; ++i) {
	if (bios_vmode[i].vi_mode == NA)
	    continue;

	if ((info->vi_width != 0)
	    && (info->vi_width != bios_vmode[i].vi_width))
		continue;
	if ((info->vi_height != 0)
	    && (info->vi_height != bios_vmode[i].vi_height))
		continue;
	if ((info->vi_cwidth != 0)
	    && (info->vi_cwidth != bios_vmode[i].vi_cwidth))
		continue;
	if ((info->vi_cheight != 0)
	    && (info->vi_cheight != bios_vmode[i].vi_cheight))
		continue;
	if ((info->vi_depth != 0)
	    && (info->vi_depth != bios_vmode[i].vi_depth))
		continue;
	if ((info->vi_planes != 0)
	    && (info->vi_planes != bios_vmode[i].vi_planes))
		continue;
	/* XXX: should check pixel format, memory model */
	if ((info->vi_flags != 0)
	    && (info->vi_flags != bios_vmode[i].vi_flags))
		continue;

	/* verify if this mode is supported on this adapter */
	if (vga_get_info(adp, bios_vmode[i].vi_mode, info))
		continue;
	return 0;
    }
    return ENODEV;
}