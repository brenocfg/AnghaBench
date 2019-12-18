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
struct unw_frame_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  unw_get_bsp (struct unw_frame_info*,unsigned long*) ; 
 int /*<<< orphan*/  unw_get_ip (struct unw_frame_info*,unsigned long*) ; 
 int /*<<< orphan*/  unw_get_sp (struct unw_frame_info*,unsigned long*) ; 
 scalar_t__ unw_unwind (struct unw_frame_info*) ; 

void
ia64_do_show_stack (struct unw_frame_info *info, void *arg)
{
	unsigned long ip, sp, bsp;

	printk("\nCall Trace:\n");
	do {
		unw_get_ip(info, &ip);
		if (ip == 0)
			break;

		unw_get_sp(info, &sp);
		unw_get_bsp(info, &bsp);
		printk(" [<%016lx>] %pS\n"
			 "                                sp=%016lx bsp=%016lx\n",
			 ip, (void *)ip, sp, bsp);
	} while (unw_unwind(info) >= 0);
}