#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int nr; TYPE_1__* objects; } ;
struct rev_info {TYPE_2__ pending; int /*<<< orphan*/  repo; } ;
struct object {int flags; scalar_t__ type; } ;
struct commit {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; struct object* item; } ;

/* Variables and functions */
 scalar_t__ OBJ_COMMIT ; 
 int UNINTERESTING ; 
 struct object* deref_tag (int /*<<< orphan*/ ,struct object*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die (char*,...) ; 

__attribute__((used)) static struct commit *check_single_commit(struct rev_info *revs)
{
	struct object *commit = NULL;
	int found = -1;
	int i;

	for (i = 0; i < revs->pending.nr; i++) {
		struct object *obj = revs->pending.objects[i].item;
		if (obj->flags & UNINTERESTING)
			continue;
		obj = deref_tag(revs->repo, obj, NULL, 0);
		if (obj->type != OBJ_COMMIT)
			die("Non commit %s?", revs->pending.objects[i].name);
		if (commit)
			die("More than one commit to dig from: %s and %s?",
			    revs->pending.objects[i].name,
			    revs->pending.objects[found].name);
		commit = obj;
		found = i;
	}

	if (!commit)
		die("No commit specified?");

	return (struct commit *) commit;
}