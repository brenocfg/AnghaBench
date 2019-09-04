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
struct object_array {int dummy; } ;
struct object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_IFINVALID ; 
 int /*<<< orphan*/  add_object_array_with_path (struct object*,char const*,struct object_array*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void add_object_array(struct object *obj, const char *name, struct object_array *array)
{
	add_object_array_with_path(obj, name, array, S_IFINVALID, NULL);
}