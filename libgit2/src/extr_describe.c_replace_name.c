#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct commit_name {unsigned int prio; TYPE_3__* tag; int /*<<< orphan*/  const sha1; } ;
typedef  scalar_t__ git_time_t ;
struct TYPE_8__ {TYPE_2__* tagger; } ;
typedef  TYPE_3__ git_tag ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_6__ {scalar_t__ time; } ;
struct TYPE_7__ {TYPE_1__ when; } ;

/* Variables and functions */
 scalar_t__ git_tag_lookup (TYPE_3__**,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int replace_name(
	git_tag **tag,
	git_repository *repo,
	struct commit_name *e,
	unsigned int prio,
	const git_oid *sha1)
{
	git_time_t e_time = 0, t_time = 0;

	if (!e || e->prio < prio)
		return 1;

	if (e->prio == 2 && prio == 2) {
		/* Multiple annotated tags point to the same commit.
		 * Select one to keep based upon their tagger date.
		 */
		git_tag *t = NULL;

		if (!e->tag) {
			if (git_tag_lookup(&t, repo, &e->sha1) < 0)
				return 1;
			e->tag = t;
		}

		if (git_tag_lookup(&t, repo, sha1) < 0)
			return 0;

		*tag = t;

		if (e->tag->tagger)
			e_time = e->tag->tagger->when.time;

		if (t->tagger)
			t_time = t->tagger->when.time;

		if (e_time < t_time)
			return 1;
	}

	return 0;
}