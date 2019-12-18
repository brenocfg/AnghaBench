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
 int /*<<< orphan*/  destroy_config () ; 
 int /*<<< orphan*/  dump_config () ; 
 int /*<<< orphan*/  read_config () ; 
 scalar_t__ verbose ; 

void
restart(void)
{
	destroy_config();
	read_config();
	if (verbose)
		dump_config();
}