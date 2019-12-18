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
struct sort_list_item {int /*<<< orphan*/  str; } ;

/* Variables and functions */
 int top_level_str_coll (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
list_coll_by_str_only(struct sort_list_item **ss1, struct sort_list_item **ss2)
{

	return (top_level_str_coll(((*ss1)->str), ((*ss2)->str)));
}