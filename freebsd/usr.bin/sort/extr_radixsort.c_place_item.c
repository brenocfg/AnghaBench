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
struct sort_level {int /*<<< orphan*/  level; struct sort_list_item** tosort; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_leaf (struct sort_level*,struct sort_list_item*) ; 
 int /*<<< orphan*/  add_to_sublevel (struct sort_level*,struct sort_list_item*,int) ; 
 int get_wc_index (struct sort_list_item*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
place_item(struct sort_level *sl, size_t item)
{
	struct sort_list_item *sli;
	int c;

	sli = sl->tosort[item];
	c = get_wc_index(sli, sl->level);

	if (c == -1)
		add_leaf(sl, sli);
	else
		add_to_sublevel(sl, sli, c);
}