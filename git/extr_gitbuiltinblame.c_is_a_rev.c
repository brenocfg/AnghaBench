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

/* Variables and functions */
 scalar_t__ OBJ_NONE ; 
 scalar_t__ get_oid (char const*,struct object_id*) ; 
 scalar_t__ oid_object_info (int /*<<< orphan*/ ,struct object_id*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static int is_a_rev(const char *name)
{
	struct object_id oid;

	if (get_oid(name, &oid))
		return 0;
	return OBJ_NONE < oid_object_info(the_repository, &oid, NULL);
}