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
struct diff_ranges {int /*<<< orphan*/  target; int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  range_set_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void diff_ranges_init(struct diff_ranges *diff)
{
	range_set_init(&diff->parent, 0);
	range_set_init(&diff->target, 0);
}