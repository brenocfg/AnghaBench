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
struct tree_content {int dummy; } ;
struct avail_tree_content {struct avail_tree_content* next_avail; int /*<<< orphan*/  entry_capacity; } ;

/* Variables and functions */
 struct avail_tree_content** avail_tree_table ; 
 unsigned int hc_entries (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void release_tree_content(struct tree_content *t)
{
	struct avail_tree_content *f = (struct avail_tree_content*)t;
	unsigned int hc = hc_entries(f->entry_capacity);
	f->next_avail = avail_tree_table[hc];
	avail_tree_table[hc] = f;
}