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

/* Variables and functions */
 int __index_pos ; 
 int do_listree_iterator (int /*<<< orphan*/ ,int,int const*,int,int*) ; 
 int /*<<< orphan*/  item_tree ; 
 int report_index (int,int) ; 

int listree_iterator (int left_len, const int *left, int right_len, int *right, int min_index_pos, int max_index_pos) {
  __index_pos = min_index_pos;
  int r = do_listree_iterator (item_tree, left_len, left, right_len, right);
  if (r < 0) { return r; }
  r = report_index (__index_pos, max_index_pos);
  if (r < 0) { return r; }
  return 0;
}