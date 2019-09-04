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
struct ref_store {int dummy; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 scalar_t__ refs_resolve_ref_unsafe (struct ref_store*,char const*,int,struct object_id*,int*) ; 

int refs_read_ref_full(struct ref_store *refs, const char *refname,
		       int resolve_flags, struct object_id *oid, int *flags)
{
	if (refs_resolve_ref_unsafe(refs, refname, resolve_flags, oid, flags))
		return 0;
	return -1;
}