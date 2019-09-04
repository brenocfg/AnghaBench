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
struct TYPE_2__ {struct blame_origin* ptr; } ;
struct blame_origin {scalar_t__ refcnt; struct blame_origin* next; int /*<<< orphan*/  commit; TYPE_1__ file; struct blame_origin* previous; } ;

/* Variables and functions */
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  free (struct blame_origin*) ; 
 struct blame_origin* get_blame_suspects (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_blame_suspects (int /*<<< orphan*/ ,struct blame_origin*) ; 

void blame_origin_decref(struct blame_origin *o)
{
	if (o && --o->refcnt <= 0) {
		struct blame_origin *p, *l = NULL;
		if (o->previous)
			blame_origin_decref(o->previous);
		free(o->file.ptr);
		/* Should be present exactly once in commit chain */
		for (p = get_blame_suspects(o->commit); p; l = p, p = p->next) {
			if (p == o) {
				if (l)
					l->next = p->next;
				else
					set_blame_suspects(o->commit, p->next);
				free(o);
				return;
			}
		}
		die("internal error in blame_origin_decref");
	}
}