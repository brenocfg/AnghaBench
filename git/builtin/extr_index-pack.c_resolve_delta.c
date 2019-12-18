#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  oid; int /*<<< orphan*/  offset; } ;
struct object_entry {TYPE_1__ idx; int /*<<< orphan*/  real_type; int /*<<< orphan*/  size; } ;
struct base_data {int /*<<< orphan*/  size; int /*<<< orphan*/  data; struct object_entry* obj; } ;
struct TYPE_4__ {scalar_t__ delta_depth; int base_object_no; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  bad_object (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  counter_lock () ; 
 int /*<<< orphan*/  counter_unlock () ; 
 scalar_t__ deepest_delta ; 
 int /*<<< orphan*/  deepest_delta_lock () ; 
 int /*<<< orphan*/  deepest_delta_unlock () ; 
 int /*<<< orphan*/  free (void*) ; 
 void* get_base_data (struct base_data*) ; 
 void* get_data_from_pack (struct object_entry*) ; 
 int /*<<< orphan*/  hash_object_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nr_resolved_deltas ; 
 TYPE_2__* obj_stat ; 
 struct object_entry* objects ; 
 int /*<<< orphan*/  patch_delta (void*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sha1_object (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ show_stat ; 
 int /*<<< orphan*/  type_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void resolve_delta(struct object_entry *delta_obj,
			  struct base_data *base, struct base_data *result)
{
	void *base_data, *delta_data;

	if (show_stat) {
		int i = delta_obj - objects;
		int j = base->obj - objects;
		obj_stat[i].delta_depth = obj_stat[j].delta_depth + 1;
		deepest_delta_lock();
		if (deepest_delta < obj_stat[i].delta_depth)
			deepest_delta = obj_stat[i].delta_depth;
		deepest_delta_unlock();
		obj_stat[i].base_object_no = j;
	}
	delta_data = get_data_from_pack(delta_obj);
	base_data = get_base_data(base);
	result->obj = delta_obj;
	result->data = patch_delta(base_data, base->size,
				   delta_data, delta_obj->size, &result->size);
	free(delta_data);
	if (!result->data)
		bad_object(delta_obj->idx.offset, _("failed to apply delta"));
	hash_object_file(result->data, result->size,
			 type_name(delta_obj->real_type), &delta_obj->idx.oid);
	sha1_object(result->data, NULL, result->size, delta_obj->real_type,
		    &delta_obj->idx.oid);
	counter_lock();
	nr_resolved_deltas++;
	counter_unlock();
}