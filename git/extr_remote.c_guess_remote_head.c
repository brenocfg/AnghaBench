#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ref {char* symref; struct ref* next; int /*<<< orphan*/  old_oid; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct ref* copy_ref (struct ref const*) ; 
 struct ref const* find_ref_by_name (struct ref const*,char*) ; 
 scalar_t__ oideq (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ starts_with (int /*<<< orphan*/ ,char*) ; 

struct ref *guess_remote_head(const struct ref *head,
			      const struct ref *refs,
			      int all)
{
	const struct ref *r;
	struct ref *list = NULL;
	struct ref **tail = &list;

	if (!head)
		return NULL;

	/*
	 * Some transports support directly peeking at
	 * where HEAD points; if that is the case, then
	 * we don't have to guess.
	 */
	if (head->symref)
		return copy_ref(find_ref_by_name(refs, head->symref));

	/* If refs/heads/master could be right, it is. */
	if (!all) {
		r = find_ref_by_name(refs, "refs/heads/master");
		if (r && oideq(&r->old_oid, &head->old_oid))
			return copy_ref(r);
	}

	/* Look for another ref that points there */
	for (r = refs; r; r = r->next) {
		if (r != head &&
		    starts_with(r->name, "refs/heads/") &&
		    oideq(&r->old_oid, &head->old_oid)) {
			*tail = copy_ref(r);
			tail = &((*tail)->next);
			if (!all)
				break;
		}
	}

	return list;
}