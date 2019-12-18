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
struct object_array {scalar_t__ nr; scalar_t__ alloc; } ;

/* Variables and functions */
 int /*<<< orphan*/  entry_unshown ; 
 int /*<<< orphan*/  object_array_filter (struct object_array*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gc_boundary(struct object_array *array)
{
	if (array->nr == array->alloc)
		object_array_filter(array, entry_unshown, NULL);
}