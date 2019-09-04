#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_14__ {int /*<<< orphan*/  commit; } ;
typedef  TYPE_2__ git_blame__origin ;
struct TYPE_15__ {int guilty; int is_boundary; TYPE_2__* suspect; struct TYPE_15__* next; } ;
typedef  TYPE_3__ git_blame__entry ;
struct TYPE_13__ {int /*<<< orphan*/  oldest_commit; } ;
struct TYPE_16__ {TYPE_1__ options; TYPE_3__* ent; } ;
typedef  TYPE_4__ git_blame ;

/* Variables and functions */
 int /*<<< orphan*/  coalesce (TYPE_4__*) ; 
 int /*<<< orphan*/  git_commit_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  origin_decref (TYPE_2__*) ; 
 int /*<<< orphan*/  origin_incref (TYPE_2__*) ; 
 int pass_blame (TYPE_4__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ same_suspect (TYPE_2__*,TYPE_2__*) ; 

int git_blame__like_git(git_blame *blame, uint32_t opt)
{
	int error = 0;

	while (true) {
		git_blame__entry *ent;
		git_blame__origin *suspect = NULL;

		/* Find a suspect to break down */
		for (ent = blame->ent; !suspect && ent; ent = ent->next)
			if (!ent->guilty)
				suspect = ent->suspect;
		if (!suspect)
			break;

		/* We'll use this suspect later in the loop, so hold on to it for now. */
		origin_incref(suspect);

		if ((error = pass_blame(blame, suspect, opt)) < 0)
			break;

		/* Take responsibility for the remaining entries */
		for (ent = blame->ent; ent; ent = ent->next) {
			if (same_suspect(ent->suspect, suspect)) {
				ent->guilty = true;
				ent->is_boundary = !git_oid_cmp(
						git_commit_id(suspect->commit),
						&blame->options.oldest_commit);
			}
		}
		origin_decref(suspect);
	}

	if (!error)
		coalesce(blame);

	return error;
}