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
struct sort_list_item {int dummy; } ;
struct sort_level {int leaves_num; int leaves_sz; struct sort_list_item** leaves; } ;

/* Variables and functions */
 struct sort_list_item** sort_realloc (struct sort_list_item**,int) ; 

__attribute__((used)) static inline void
add_leaf(struct sort_level *sl, struct sort_list_item *item)
{

	if (++(sl->leaves_num) > sl->leaves_sz) {
		sl->leaves_sz = sl->leaves_num + 128;
		sl->leaves = sort_realloc(sl->leaves,
		    (sizeof(struct sort_list_item*) * (sl->leaves_sz)));
	}
	sl->leaves[sl->leaves_num - 1] = item;
}