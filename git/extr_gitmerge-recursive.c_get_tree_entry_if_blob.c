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
struct object_id {int dummy; } ;

/* Variables and functions */
 scalar_t__ S_ISDIR (unsigned int) ; 
 int get_tree_entry (struct object_id const*,char const*,struct object_id*,unsigned int*) ; 
 int /*<<< orphan*/  null_oid ; 
 int /*<<< orphan*/  oidcpy (struct object_id*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int get_tree_entry_if_blob(const struct object_id *tree,
				  const char *path,
				  struct object_id *hashy,
				  unsigned int *mode_o)
{
	int ret;

	ret = get_tree_entry(tree, path, hashy, mode_o);
	if (S_ISDIR(*mode_o)) {
		oidcpy(hashy, &null_oid);
		*mode_o = 0;
	}
	return ret;
}