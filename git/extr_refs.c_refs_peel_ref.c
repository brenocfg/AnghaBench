#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ref_store {int dummy; } ;
struct object_id {int dummy; } ;
struct TYPE_3__ {char const* refname; } ;

/* Variables and functions */
 int /*<<< orphan*/  RESOLVE_REF_READING ; 
 TYPE_1__* current_ref_iter ; 
 int /*<<< orphan*/  oidcpy (struct object_id*,struct object_id*) ; 
 int peel_object (struct object_id*,struct object_id*) ; 
 scalar_t__ ref_iterator_peel (TYPE_1__*,struct object_id*) ; 
 scalar_t__ refs_read_ref_full (struct ref_store*,char const*,int /*<<< orphan*/ ,struct object_id*,int*) ; 

int refs_peel_ref(struct ref_store *refs, const char *refname,
		  struct object_id *oid)
{
	int flag;
	struct object_id base;

	if (current_ref_iter && current_ref_iter->refname == refname) {
		struct object_id peeled;

		if (ref_iterator_peel(current_ref_iter, &peeled))
			return -1;
		oidcpy(oid, &peeled);
		return 0;
	}

	if (refs_read_ref_full(refs, refname,
			       RESOLVE_REF_READING, &base, &flag))
		return -1;

	return peel_object(&base, oid);
}