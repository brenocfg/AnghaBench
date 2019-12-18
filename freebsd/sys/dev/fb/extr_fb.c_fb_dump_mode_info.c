#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int vi_mode; int vi_flags; int vi_width; int vi_height; int vi_depth; int vi_planes; int vi_cwidth; int vi_cheight; scalar_t__ vi_window; } ;
typedef  TYPE_1__ video_info_t ;
struct TYPE_6__ {char* va_unit; int va_name; } ;
typedef  TYPE_2__ video_adapter_t ;
typedef  int /*<<< orphan*/  u_long ;

/* Variables and functions */
 int V_INFO_GRAPHICS ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void
fb_dump_mode_info(char *driver, video_adapter_t *adp, video_info_t *info,
		  int level)
{
    if (level <= 0)
	return;

    printf("%s%d: %s, mode:%d, flags:0x%x ", 
	   driver, adp->va_unit, adp->va_name, info->vi_mode, info->vi_flags);
    if (info->vi_flags & V_INFO_GRAPHICS)
	printf("G %dx%dx%d, %d plane(s), font:%dx%d, ",
	       info->vi_width, info->vi_height, 
	       info->vi_depth, info->vi_planes, 
	       info->vi_cwidth, info->vi_cheight); 
    else
	printf("T %dx%d, font:%dx%d, ",
	       info->vi_width, info->vi_height, 
	       info->vi_cwidth, info->vi_cheight); 
    printf("win:0x%lx\n", (u_long)info->vi_window);
}