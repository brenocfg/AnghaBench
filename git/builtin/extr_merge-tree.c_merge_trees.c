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
struct traverse_info {int /*<<< orphan*/  fn; } ;

/* Variables and functions */
 int /*<<< orphan*/  setup_traverse_info (struct traverse_info*,char const*) ; 
 int /*<<< orphan*/  the_index ; 
 int /*<<< orphan*/  threeway_callback ; 
 int /*<<< orphan*/  traverse_trees (int /*<<< orphan*/ *,int,struct tree_desc*,struct traverse_info*) ; 

__attribute__((used)) static void merge_trees(struct tree_desc t[3], const char *base)
{
	struct traverse_info info;

	setup_traverse_info(&info, base);
	info.fn = threeway_callback;
	traverse_trees(&the_index, 3, t, &info);
}