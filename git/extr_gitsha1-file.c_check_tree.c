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
struct name_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_tree_desc (struct tree_desc*,void const*,size_t) ; 
 scalar_t__ tree_entry (struct tree_desc*,struct name_entry*) ; 

__attribute__((used)) static void check_tree(const void *buf, size_t size)
{
	struct tree_desc desc;
	struct name_entry entry;

	init_tree_desc(&desc, buf, size);
	while (tree_entry(&desc, &entry))
		/* do nothing
		 * tree_entry() will die() on malformed entries */
		;
}