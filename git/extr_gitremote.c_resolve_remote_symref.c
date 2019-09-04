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
struct ref {int /*<<< orphan*/  old_oid; int /*<<< orphan*/  name; int /*<<< orphan*/  symref; struct ref* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  oidcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int resolve_remote_symref(struct ref *ref, struct ref *list)
{
	if (!ref->symref)
		return 0;
	for (; list; list = list->next)
		if (!strcmp(ref->symref, list->name)) {
			oidcpy(&ref->old_oid, &list->old_oid);
			return 0;
		}
	return 1;
}