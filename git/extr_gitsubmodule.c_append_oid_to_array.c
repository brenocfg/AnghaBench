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
struct oid_array {int dummy; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  oid_array_append (struct oid_array*,struct object_id const*) ; 

__attribute__((used)) static int append_oid_to_array(const char *ref, const struct object_id *oid,
			       int flags, void *data)
{
	struct oid_array *array = data;
	oid_array_append(array, oid);
	return 0;
}