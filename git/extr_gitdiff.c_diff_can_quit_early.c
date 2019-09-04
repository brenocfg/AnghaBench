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
struct TYPE_2__ {scalar_t__ has_changes; scalar_t__ quick; } ;
struct diff_options {TYPE_1__ flags; int /*<<< orphan*/  filter; } ;

/* Variables and functions */

int diff_can_quit_early(struct diff_options *opt)
{
	return (opt->flags.quick &&
		!opt->filter &&
		opt->flags.has_changes);
}