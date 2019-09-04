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
struct repository {int dummy; } ;
struct packed_git {int dummy; } ;
struct delta_base_cache_entry {int type; unsigned long size; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  off_t ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;

/* Variables and functions */
 struct delta_base_cache_entry* get_delta_base_cache_entry (struct packed_git*,int /*<<< orphan*/ ) ; 
 void* unpack_entry (struct repository*,struct packed_git*,int /*<<< orphan*/ ,int*,unsigned long*) ; 
 void* xmemdupz (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void *cache_or_unpack_entry(struct repository *r, struct packed_git *p,
				   off_t base_offset, unsigned long *base_size,
				   enum object_type *type)
{
	struct delta_base_cache_entry *ent;

	ent = get_delta_base_cache_entry(p, base_offset);
	if (!ent)
		return unpack_entry(r, p, base_offset, type, base_size);

	if (type)
		*type = ent->type;
	if (base_size)
		*base_size = ent->size;
	return xmemdupz(ent->data, ent->size);
}