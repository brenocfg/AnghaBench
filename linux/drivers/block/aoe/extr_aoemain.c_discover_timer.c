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
struct timer_list {int dummy; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  aoecmd_cfg (int,int) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (struct timer_list*,scalar_t__) ; 

__attribute__((used)) static void discover_timer(struct timer_list *t)
{
	mod_timer(t, jiffies + HZ * 60); /* one minute */

	aoecmd_cfg(0xffff, 0xff);
}