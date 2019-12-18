#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ guilty; scalar_t__ s_lno; scalar_t__ num_lines; scalar_t__ score; int /*<<< orphan*/  suspect; struct TYPE_5__* prev; struct TYPE_5__* next; } ;
typedef  TYPE_1__ git_blame__entry ;
struct TYPE_6__ {TYPE_1__* ent; } ;
typedef  TYPE_2__ git_blame ;

/* Variables and functions */
 int /*<<< orphan*/  git__free (TYPE_1__*) ; 
 int /*<<< orphan*/  origin_decref (int /*<<< orphan*/ ) ; 
 scalar_t__ same_suspect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void coalesce(git_blame *blame)
{
	git_blame__entry *ent, *next;

	for (ent=blame->ent; ent && (next = ent->next); ent = next) {
		if (same_suspect(ent->suspect, next->suspect) &&
		    ent->guilty == next->guilty &&
		    ent->s_lno + ent->num_lines == next->s_lno)
		{
			ent->num_lines += next->num_lines;
			ent->next = next->next;
			if (ent->next)
				ent->next->prev = ent;
			origin_decref(next->suspect);
			git__free(next);
			ent->score = 0;
			next = ent; /* again */
		}
	}
}