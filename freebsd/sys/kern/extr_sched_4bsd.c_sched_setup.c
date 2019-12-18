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
 int /*<<< orphan*/  sched_load_add () ; 
 int /*<<< orphan*/  setup_runqs () ; 

__attribute__((used)) static void
sched_setup(void *dummy)
{

	setup_runqs();

	/* Account for thread0. */
	sched_load_add();
}