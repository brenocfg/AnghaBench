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
typedef  int /*<<< orphan*/  Z ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int get_index_pos (int,int const*) ; 
 int index_entries ; 
 int /*<<< orphan*/  index_load_unsure (int,int const*,int,int const*) ; 
 int /*<<< orphan*/  item_tree ; 
 scalar_t__ key_cmp (int,int const*,int,int const*) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tree_count (int /*<<< orphan*/ ,int,int const*,int,int const*,int*) ; 

int get_range_count (int left_len, const int *left, int right_len, const int *right) {
  if (left_len && right_len && key_cmp (left_len, left, right_len, right) > 0) {
    return 0;
  }
  int min_index_pos = left_len ? 0 : get_index_pos (left_len, left);
  int max_index_pos = right_len ? index_entries : get_index_pos (right_len, right);
  if (min_index_pos == -2 || max_index_pos == -2) {
    return -2;
  }
  int Z[3];
  memset (Z, 0, sizeof (Z));
  tree_count (item_tree, left_len, left, right_len, right, Z);
  if (Z[1] || Z[2]) {
    index_load_unsure (left_len, left, right_len, right);
    return -2;
  } else {
    assert (Z[0] + max_index_pos - min_index_pos >= 0);
    return Z[0] + max_index_pos - min_index_pos;
  }
}