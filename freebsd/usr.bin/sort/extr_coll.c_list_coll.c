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

/* Variables and functions */
 int list_coll_offset (struct sort_list_item**,struct sort_list_item**,int /*<<< orphan*/ ) ; 

int
list_coll(struct sort_list_item **ss1, struct sort_list_item **ss2)
{

	return (list_coll_offset(ss1, ss2, 0));
}