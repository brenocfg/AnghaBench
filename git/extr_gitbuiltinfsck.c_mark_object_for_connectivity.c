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
struct object_id {int /*<<< orphan*/  hash; } ;
struct object {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  HAS_OBJ ; 
 struct object* lookup_unknown_object (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mark_object_for_connectivity(const struct object_id *oid)
{
	struct object *obj = lookup_unknown_object(oid->hash);
	obj->flags |= HAS_OBJ;
}