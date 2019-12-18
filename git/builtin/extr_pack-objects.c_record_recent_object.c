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
struct object {int /*<<< orphan*/  oid; } ;

/* Variables and functions */
 int /*<<< orphan*/  oid_array_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  recent_objects ; 

__attribute__((used)) static void record_recent_object(struct object *obj,
				 const char *name,
				 void *data)
{
	oid_array_append(&recent_objects, &obj->oid);
}