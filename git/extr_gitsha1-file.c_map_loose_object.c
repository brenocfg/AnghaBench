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

/* Variables and functions */
 void* map_loose_object_1 (struct repository*,int /*<<< orphan*/ *,struct object_id const*,unsigned long*) ; 

void *map_loose_object(struct repository *r,
		       const struct object_id *oid,
		       unsigned long *size)
{
	return map_loose_object_1(r, NULL, oid, size);
}