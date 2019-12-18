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
struct packing_data {struct object_entry const* objects; struct packed_git** in_pack; struct packed_git** in_pack_by_idx; } ;
struct packed_git {int dummy; } ;
struct object_entry {size_t in_pack_idx; } ;

/* Variables and functions */

__attribute__((used)) static inline struct packed_git *oe_in_pack(const struct packing_data *pack,
					    const struct object_entry *e)
{
	if (pack->in_pack_by_idx)
		return pack->in_pack_by_idx[e->in_pack_idx];
	else
		return pack->in_pack[e - pack->objects];
}