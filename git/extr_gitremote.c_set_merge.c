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
struct remote {int dummy; } ;
struct object_id {int dummy; } ;
struct branch {int merge_nr; int /*<<< orphan*/ * merge_name; TYPE_1__** merge; int /*<<< orphan*/  remote_name; } ;
struct TYPE_2__ {char* dst; void* src; } ;

/* Variables and functions */
 int dwim_ref (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct object_id*,char**) ; 
 int /*<<< orphan*/  remote_find_tracking (struct remote*,TYPE_1__*) ; 
 struct remote* remote_get (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 void* xcalloc (int,int) ; 
 void* xstrdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_merge(struct branch *ret)
{
	struct remote *remote;
	char *ref;
	struct object_id oid;
	int i;

	if (!ret)
		return; /* no branch */
	if (ret->merge)
		return; /* already run */
	if (!ret->remote_name || !ret->merge_nr) {
		/*
		 * no merge config; let's make sure we don't confuse callers
		 * with a non-zero merge_nr but a NULL merge
		 */
		ret->merge_nr = 0;
		return;
	}

	remote = remote_get(ret->remote_name);

	ret->merge = xcalloc(ret->merge_nr, sizeof(*ret->merge));
	for (i = 0; i < ret->merge_nr; i++) {
		ret->merge[i] = xcalloc(1, sizeof(**ret->merge));
		ret->merge[i]->src = xstrdup(ret->merge_name[i]);
		if (!remote_find_tracking(remote, ret->merge[i]) ||
		    strcmp(ret->remote_name, "."))
			continue;
		if (dwim_ref(ret->merge_name[i], strlen(ret->merge_name[i]),
			     &oid, &ref) == 1)
			ret->merge[i]->dst = ref;
		else
			ret->merge[i]->dst = xstrdup(ret->merge_name[i]);
	}
}