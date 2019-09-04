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
struct packing_data {struct object_entry* objects; } ;
struct object_entry {int delta_idx; } ;

/* Variables and functions */

__attribute__((used)) static inline void oe_set_delta(struct packing_data *pack,
				struct object_entry *e,
				struct object_entry *delta)
{
	if (delta)
		e->delta_idx = (delta - pack->objects) + 1;
	else
		e->delta_idx = 0;
}