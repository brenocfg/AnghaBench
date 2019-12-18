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
struct vt_window {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  vt_late_window_switch (struct vt_window*) ; 

__attribute__((used)) static void
vt_switch_timer(void *arg)
{

	(void)vt_late_window_switch((struct vt_window *)arg);
}