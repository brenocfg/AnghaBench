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
struct fsi_master_gpio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clock_toggle (struct fsi_master_gpio*,int) ; 
 int /*<<< orphan*/  set_sda_output (struct fsi_master_gpio*,int) ; 
 int /*<<< orphan*/  trace_fsi_master_gpio_clock_zeros (struct fsi_master_gpio*,int) ; 

__attribute__((used)) static void clock_zeros(struct fsi_master_gpio *master, int count)
{
	trace_fsi_master_gpio_clock_zeros(master, count);
	set_sda_output(master, 1);
	clock_toggle(master, count);
}