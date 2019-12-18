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
struct repository {int dummy; } ;
struct object_id {int dummy; } ;
struct object_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GET_OID_ONLY_TO_DIE ; 
 int /*<<< orphan*/  get_oid_with_context_1 (struct repository*,char const*,int /*<<< orphan*/ ,char const*,struct object_id*,struct object_context*) ; 

void maybe_die_on_misspelt_object_name(struct repository *r,
				       const char *name,
				       const char *prefix)
{
	struct object_context oc;
	struct object_id oid;
	get_oid_with_context_1(r, name, GET_OID_ONLY_TO_DIE,
			       prefix, &oid, &oc);
}