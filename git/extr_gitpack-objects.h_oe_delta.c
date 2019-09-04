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
struct packing_data {struct object_entry* objects; struct object_entry* ext_bases; } ;
struct object_entry {int delta_idx; scalar_t__ ext_base; } ;

/* Variables and functions */

__attribute__((used)) static inline struct object_entry *oe_delta(
		const struct packing_data *pack,
		const struct object_entry *e)
{
	if (!e->delta_idx)
		return NULL;
	if (e->ext_base)
		return &pack->ext_bases[e->delta_idx - 1];
	else
		return &pack->objects[e->delta_idx - 1];
}