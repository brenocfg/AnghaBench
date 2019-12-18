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
struct tree_desc {int dummy; } ;
struct repository {int dummy; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  die (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_tree_desc (struct tree_desc*,void*,unsigned long) ; 
 int /*<<< orphan*/  oid_to_hex (struct object_id const*) ; 
 void* read_object_with_reference (struct repository*,struct object_id const*,int /*<<< orphan*/ ,unsigned long*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tree_type ; 

void *fill_tree_descriptor(struct repository *r,
			   struct tree_desc *desc,
			   const struct object_id *oid)
{
	unsigned long size = 0;
	void *buf = NULL;

	if (oid) {
		buf = read_object_with_reference(r, oid, tree_type, &size, NULL);
		if (!buf)
			die("unable to read tree %s", oid_to_hex(oid));
	}
	init_tree_desc(desc, buf, size);
	return buf;
}