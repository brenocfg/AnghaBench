#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int nr; TYPE_2__* rev; } ;
struct rev_info {TYPE_3__ cmdline; } ;
struct object_id {int dummy; } ;
struct TYPE_5__ {int flags; char* name; TYPE_1__* item; } ;
struct TYPE_4__ {struct object_id oid; } ;

/* Variables and functions */
 int UNINTERESTING ; 
 scalar_t__ dwim_ref (char const*,int /*<<< orphan*/ ,struct object_id*,char**) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ oideq (struct object_id const*,struct object_id*) ; 
 scalar_t__ skip_prefix (char*,char*,char const**) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 char* xstrdup (char const*) ; 

__attribute__((used)) static char *find_branch_name(struct rev_info *rev)
{
	int i, positive = -1;
	struct object_id branch_oid;
	const struct object_id *tip_oid;
	const char *ref, *v;
	char *full_ref, *branch = NULL;

	for (i = 0; i < rev->cmdline.nr; i++) {
		if (rev->cmdline.rev[i].flags & UNINTERESTING)
			continue;
		if (positive < 0)
			positive = i;
		else
			return NULL;
	}
	if (positive < 0)
		return NULL;
	ref = rev->cmdline.rev[positive].name;
	tip_oid = &rev->cmdline.rev[positive].item->oid;
	if (dwim_ref(ref, strlen(ref), &branch_oid, &full_ref) &&
	    skip_prefix(full_ref, "refs/heads/", &v) &&
	    oideq(tip_oid, &branch_oid))
		branch = xstrdup(v);
	free(full_ref);
	return branch;
}