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
 int /*<<< orphan*/  last_cmd_status ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdtgroup_mutex ; 
 int /*<<< orphan*/  seq_buf_clear (int /*<<< orphan*/ *) ; 

void rdt_last_cmd_clear(void)
{
	lockdep_assert_held(&rdtgroup_mutex);
	seq_buf_clear(&last_cmd_status);
}