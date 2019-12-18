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
struct ref {int /*<<< orphan*/  old_oid; struct ref* next; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  oidcpy (struct object_id*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iterate_ref_map(void *cb_data, struct object_id *oid)
{
	struct ref **rm = cb_data;
	struct ref *ref = *rm;

	if (!ref)
		return -1; /* end of the list */
	*rm = ref->next;
	oidcpy(oid, &ref->old_oid);
	return 0;
}