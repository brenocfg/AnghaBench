#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ pattern; } ;

/* Variables and functions */
 int /*<<< orphan*/  ensure_tag_pattern_match (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  g_repo ; 
 TYPE_1__* matches ; 

void test_object_tag_list__list_by_pattern(void)
{
	/* list all tag names from the repository matching a specified pattern */
	size_t i = 0;
	while (matches[i].pattern)
		ensure_tag_pattern_match(g_repo, &matches[i++]);
}