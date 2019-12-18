#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_blame__origin ;
struct TYPE_4__ {size_t s_lno; size_t num_lines; int /*<<< orphan*/  suspect; scalar_t__ guilty; struct TYPE_4__* next; } ;
typedef  TYPE_1__ git_blame__entry ;
struct TYPE_5__ {TYPE_1__* ent; } ;
typedef  TYPE_2__ git_blame ;

/* Variables and functions */
 int /*<<< orphan*/  same_suspect (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool find_last_in_target(size_t *out, git_blame *blame, git_blame__origin *target)
{
	git_blame__entry *e;
	size_t last_in_target = 0;
	bool found = false;

	*out = 0;

	for (e=blame->ent; e; e=e->next) {
		if (e->guilty || !same_suspect(e->suspect, target))
			continue;
		if (last_in_target < e->s_lno + e->num_lines) {
			found = true;
			last_in_target = e->s_lno + e->num_lines;
		}
	}

	*out = last_in_target;
	return found;
}