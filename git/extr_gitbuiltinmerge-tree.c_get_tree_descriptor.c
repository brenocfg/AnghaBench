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

/* Variables and functions */
 int /*<<< orphan*/  die (char*,char const*) ; 
 void* fill_tree_descriptor (struct tree_desc*,struct object_id*) ; 
 scalar_t__ get_oid (char const*,struct object_id*) ; 

__attribute__((used)) static void *get_tree_descriptor(struct tree_desc *desc, const char *rev)
{
	struct object_id oid;
	void *buf;

	if (get_oid(rev, &oid))
		die("unknown rev %s", rev);
	buf = fill_tree_descriptor(desc, &oid);
	if (!buf)
		die("%s is not a tree", rev);
	return buf;
}