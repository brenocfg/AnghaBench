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
typedef  int /*<<< orphan*/  module_t ;

/* Variables and functions */

__attribute__((used)) static int
mod_handler(module_t mod, int type, void *data)
{

	/*
	 * Nothing to do here: the SYSINIT/SYSUNINIT defined above run
	 * automatically at module load/unload time.
	 */
	return (0);
}