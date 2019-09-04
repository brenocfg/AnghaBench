#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int /*<<< orphan*/  tr2_sid_compute () ; 
 TYPE_1__ tr2sid_buf ; 
 int tr2sid_nr_git_parents ; 

int tr2_sid_depth(void)
{
	if (!tr2sid_buf.len)
		tr2_sid_compute();

	return tr2sid_nr_git_parents;
}