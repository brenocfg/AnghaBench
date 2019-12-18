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
struct packing_data {unsigned long oe_delta_size_limit; unsigned long* delta_size; struct object_entry* objects; int /*<<< orphan*/  nr_alloc; } ;
struct object_entry {unsigned long delta_size_; int delta_size_valid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_ARRAY (unsigned long*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  packing_data_lock (struct packing_data*) ; 
 int /*<<< orphan*/  packing_data_unlock (struct packing_data*) ; 

__attribute__((used)) static inline void oe_set_delta_size(struct packing_data *pack,
				     struct object_entry *e,
				     unsigned long size)
{
	if (size < pack->oe_delta_size_limit) {
		e->delta_size_ = size;
		e->delta_size_valid = 1;
	} else {
		packing_data_lock(pack);
		if (!pack->delta_size)
			ALLOC_ARRAY(pack->delta_size, pack->nr_alloc);
		packing_data_unlock(pack);

		pack->delta_size[e - pack->objects] = size;
		e->delta_size_valid = 0;
	}
}