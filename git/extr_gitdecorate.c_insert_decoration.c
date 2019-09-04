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
struct decoration {int size; int /*<<< orphan*/  nr; struct decoration_entry* entries; } ;

/* Variables and functions */
 unsigned int hash_obj (struct object const*,int) ; 

__attribute__((used)) static void *insert_decoration(struct decoration *n, const struct object *base, void *decoration)
{
	int size = n->size;
	struct decoration_entry *entries = n->entries;
	unsigned int j = hash_obj(base, size);

	while (entries[j].base) {
		if (entries[j].base == base) {
			void *old = entries[j].decoration;
			entries[j].decoration = decoration;
			return old;
		}
		if (++j >= size)
			j = 0;
	}
	entries[j].base = base;
	entries[j].decoration = decoration;
	n->nr++;
	return NULL;
}