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
struct object_id {int dummy; } ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;

/* Variables and functions */
 int OBJ_TREE ; 
 int /*<<< orphan*/  die (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_tree_desc (struct tree_desc*,void*,unsigned long) ; 
 int /*<<< orphan*/  oid_to_hex (struct object_id const*) ; 
 void* read_object_file (struct object_id const*,int*,unsigned long*) ; 

__attribute__((used)) static void *fill_tree_desc_strict(struct tree_desc *desc,
				   const struct object_id *hash)
{
	void *buffer;
	enum object_type type;
	unsigned long size;

	buffer = read_object_file(hash, &type, &size);
	if (!buffer)
		die("unable to read tree (%s)", oid_to_hex(hash));
	if (type != OBJ_TREE)
		die("%s is not a tree", oid_to_hex(hash));
	init_tree_desc(desc, buffer, size);
	return buffer;
}