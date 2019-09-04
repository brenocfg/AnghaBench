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
struct object_entry {int dummy; } ;
struct base_data {int /*<<< orphan*/ * data; struct object_entry* obj; } ;

/* Variables and functions */
 struct base_data* alloc_base_data () ; 
 int /*<<< orphan*/  find_unresolved_deltas (struct base_data*) ; 

__attribute__((used)) static void resolve_base(struct object_entry *obj)
{
	struct base_data *base_obj = alloc_base_data();
	base_obj->obj = obj;
	base_obj->data = NULL;
	find_unresolved_deltas(base_obj);
}