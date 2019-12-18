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
struct fsi_master_gpio {int /*<<< orphan*/  t_echo_delay; } ;

/* Variables and functions */
 int /*<<< orphan*/  clock_zeros (struct fsi_master_gpio*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void echo_delay(struct fsi_master_gpio *master)
{
	clock_zeros(master, master->t_echo_delay);
}