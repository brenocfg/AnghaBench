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
 int /*<<< orphan*/  die (char*,char const*) ; 
 void* fill_tree_descriptor (struct repository*,struct tree_desc*,struct object_id*) ; 
 scalar_t__ repo_get_oid (struct repository*,char const*,struct object_id*) ; 

__attribute__((used)) static void *get_tree_descriptor(struct repository *r,
				 struct tree_desc *desc,
				 const char *rev)
{
	struct object_id oid;
	void *buf;

	if (repo_get_oid(r, rev, &oid))
		die("unknown rev %s", rev);
	buf = fill_tree_descriptor(r, desc, &oid);
	if (!buf)
		die("%s is not a tree", rev);
	return buf;
}