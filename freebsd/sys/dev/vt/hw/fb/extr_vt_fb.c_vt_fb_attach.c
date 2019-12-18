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
struct fb_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  vt_allocate (int /*<<< orphan*/ *,struct fb_info*) ; 
 int /*<<< orphan*/  vt_fb_driver ; 

int
vt_fb_attach(struct fb_info *info)
{

	vt_allocate(&vt_fb_driver, info);

	return (0);
}