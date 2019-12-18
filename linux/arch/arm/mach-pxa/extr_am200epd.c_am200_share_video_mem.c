#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ xres; scalar_t__ yres; } ;
struct fb_info {TYPE_3__* fbops; int /*<<< orphan*/  screen_base; TYPE_1__ var; } ;
struct TYPE_10__ {struct fb_info* host_fbinfo; int /*<<< orphan*/  metromem; } ;
struct TYPE_9__ {TYPE_2__* modes; } ;
struct TYPE_8__ {int /*<<< orphan*/  owner; } ;
struct TYPE_7__ {scalar_t__ xres; scalar_t__ yres; } ;

/* Variables and functions */
 int ENODEV ; 
 TYPE_5__ am200_board ; 
 TYPE_4__ am200_fb_info ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int am200_share_video_mem(struct fb_info *info)
{
	/* rough check if this is our desired fb and not something else */
	if ((info->var.xres != am200_fb_info.modes->xres)
		|| (info->var.yres != am200_fb_info.modes->yres))
		return 0;

	/* we've now been notified that we have our new fb */
	am200_board.metromem = info->screen_base;
	am200_board.host_fbinfo = info;

	/* try to refcount host drv since we are the consumer after this */
	if (!try_module_get(info->fbops->owner))
		return -ENODEV;

	return 0;
}