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
struct commit {TYPE_1__* parents; } ;
struct TYPE_2__ {struct commit* item; scalar_t__ next; } ;

/* Variables and functions */
 int /*<<< orphan*/  parse_commit (struct commit*) ; 

__attribute__((used)) static int is_linear_history(struct commit *from, struct commit *to)
{
	while (to && to != from) {
		parse_commit(to);
		if (!to->parents)
			return 1;
		if (to->parents->next)
			return 0;
		to = to->parents->item;
	}
	return 1;
}