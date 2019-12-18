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
struct vt_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  vt_resume (struct vt_device*) ; 

void
vt_fb_resume(struct vt_device *vd)
{

	vt_resume(vd);
}