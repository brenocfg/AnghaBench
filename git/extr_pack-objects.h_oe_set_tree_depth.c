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
struct packing_data {unsigned int* tree_depth; struct object_entry* objects; int /*<<< orphan*/  nr_alloc; } ;
struct object_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CALLOC_ARRAY (unsigned int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void oe_set_tree_depth(struct packing_data *pack,
				     struct object_entry *e,
				     unsigned int tree_depth)
{
	if (!pack->tree_depth)
		CALLOC_ARRAY(pack->tree_depth, pack->nr_alloc);
	pack->tree_depth[e - pack->objects] = tree_depth;
}