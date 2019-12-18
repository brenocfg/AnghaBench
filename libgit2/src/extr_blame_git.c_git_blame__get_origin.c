#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_commit ;
typedef  int /*<<< orphan*/  git_blame__origin ;
struct TYPE_5__ {TYPE_3__* suspect; struct TYPE_5__* next; } ;
typedef  TYPE_1__ git_blame__entry ;
struct TYPE_6__ {TYPE_1__* ent; } ;
typedef  TYPE_2__ git_blame ;
struct TYPE_7__ {int /*<<< orphan*/  path; int /*<<< orphan*/ * commit; } ;

/* Variables and functions */
 int make_origin (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * origin_incref (TYPE_3__*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

int git_blame__get_origin(
		git_blame__origin **out,
		git_blame *blame,
		git_commit *commit,
		const char *path)
{
	git_blame__entry *e;

	for (e = blame->ent; e; e = e->next) {
		if (e->suspect->commit == commit && !strcmp(e->suspect->path, path)) {
			*out = origin_incref(e->suspect);
		}
	}
	return make_origin(out, commit, path);
}