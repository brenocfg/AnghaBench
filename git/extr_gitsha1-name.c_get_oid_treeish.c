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
struct object_id {int dummy; } ;
struct object_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GET_OID_TREEISH ; 
 int get_oid_with_context (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,struct object_id*,struct object_context*) ; 
 int /*<<< orphan*/  the_repository ; 

int get_oid_treeish(const char *name, struct object_id *oid)
{
	struct object_context unused;
	return get_oid_with_context(the_repository,
				    name, GET_OID_TREEISH,
				    oid, &unused);
}