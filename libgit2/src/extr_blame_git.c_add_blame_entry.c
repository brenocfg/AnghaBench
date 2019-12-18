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
struct TYPE_5__ {scalar_t__ lno; struct TYPE_5__* prev; struct TYPE_5__* next; int /*<<< orphan*/  suspect; } ;
typedef  TYPE_1__ git_blame__entry ;
struct TYPE_6__ {TYPE_1__* ent; } ;
typedef  TYPE_2__ git_blame ;

/* Variables and functions */
 int /*<<< orphan*/  origin_incref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void add_blame_entry(git_blame *blame, git_blame__entry *e)
{
	git_blame__entry *ent, *prev = NULL;

	origin_incref(e->suspect);

	for (ent = blame->ent; ent && ent->lno < e->lno; ent = ent->next)
		prev = ent;

	/* prev, if not NULL, is the last one that is below e */
	e->prev = prev;
	if (prev) {
		e->next = prev->next;
		prev->next = e;
	} else {
		e->next = blame->ent;
		blame->ent = e;
	}
	if (e->next)
		e->next->prev = e;
}