#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct fb_list_entry {TYPE_1__* fb_si; struct fb_info* fb_info; } ;
struct fb_info {TYPE_1__* fb_cdev; } ;
struct TYPE_2__ {struct fb_info* si_drv1; } ;

/* Variables and functions */
 int /*<<< orphan*/  GID_WHEEL ; 
 int /*<<< orphan*/  UID_ROOT ; 
 int /*<<< orphan*/  fb_cdevsw ; 
 TYPE_1__* make_dev (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int) ; 

__attribute__((used)) static int
fb_init(struct fb_list_entry *entry, int unit)
{
	struct fb_info *info;

	info = entry->fb_info;
	entry->fb_si = make_dev(&fb_cdevsw, unit, UID_ROOT, GID_WHEEL,
	    0600, "fb%d", unit);
	entry->fb_si->si_drv1 = info;
	info->fb_cdev = entry->fb_si;

	return (0);
}