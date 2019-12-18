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
struct object {int dummy; } ;
struct decoration_entry {void* decoration; struct object const* base; } ;
struct decoration {unsigned int size; struct decoration_entry* entries; } ;

/* Variables and functions */
 unsigned int hash_obj (struct object const*,unsigned int) ; 

void *lookup_decoration(struct decoration *n, const struct object *obj)
{
	unsigned int j;

	/* nothing to lookup */
	if (!n->size)
		return NULL;
	j = hash_obj(obj, n->size);
	for (;;) {
		struct decoration_entry *ref = n->entries + j;
		if (ref->base == obj)
			return ref->decoration;
		if (!ref->base)
			return NULL;
		if (++j == n->size)
			j = 0;
	}
}