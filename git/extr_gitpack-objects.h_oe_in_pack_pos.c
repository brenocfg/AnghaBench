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
struct packing_data {unsigned int* in_pack_pos; struct object_entry const* objects; } ;
struct object_entry {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline unsigned int oe_in_pack_pos(const struct packing_data *pack,
					  const struct object_entry *e)
{
	return pack->in_pack_pos[e - pack->objects];
}