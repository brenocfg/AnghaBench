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
struct oid_array {int /*<<< orphan*/  nr; int /*<<< orphan*/  oid; int /*<<< orphan*/  sorted; } ;
struct object_id {int /*<<< orphan*/  hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  oid_array_sort (struct oid_array*) ; 
 int /*<<< orphan*/  sha1_access ; 
 int sha1_pos (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int oid_array_lookup(struct oid_array *array, const struct object_id *oid)
{
	if (!array->sorted)
		oid_array_sort(array);
	return sha1_pos(oid->hash, array->oid, array->nr, sha1_access);
}