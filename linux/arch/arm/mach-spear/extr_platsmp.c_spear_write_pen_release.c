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

/* Variables and functions */
 int /*<<< orphan*/  smp_wmb () ; 
 int spear_pen_release ; 
 int /*<<< orphan*/  sync_cache_w (int*) ; 

__attribute__((used)) static void spear_write_pen_release(int val)
{
	spear_pen_release = val;
	smp_wmb();
	sync_cache_w(&spear_pen_release);
}