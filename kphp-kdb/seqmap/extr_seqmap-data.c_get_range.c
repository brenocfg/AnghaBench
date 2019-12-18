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
 int* B ; 
 scalar_t__ Bpos ; 
 int Bsize ; 
 int* RR ; 
 int R_MAX ; 
 int Rmax ; 
 scalar_t__ Rpos ; 
 scalar_t__ Rt ; 
 int /*<<< orphan*/  __array_report ; 
 int /*<<< orphan*/  __tree_report ; 
 int /*<<< orphan*/  array_ifwrite ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cmp ; 
 int get_index_pos (int,int const*) ; 
 int index_entries ; 
 int /*<<< orphan*/  item_tree ; 
 scalar_t__ key_cmp (int,int const*,int,int*) ; 
 int listree_iterator (int,int const*,int,int*,int,int) ; 
 int lrand48 () ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qsort (int*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree_count (int /*<<< orphan*/ ,int,int const*,int,int*,int*) ; 
 int /*<<< orphan*/  tree_ifwrite ; 

int get_range (int left_len, const int *left, int right_len, int *right, int limit, int *R, int size, int *cnt, int *total) {
  if (left_len && right_len && key_cmp (left_len, left, right_len, right) > 0) {
    *cnt = *total = 0;
    return 0;
  }
  if (limit > R_MAX) {
    limit = R_MAX;
  }
  int min_index_pos = left_len ? 0 : get_index_pos (left_len, left);
  int max_index_pos = right_len ? index_entries : get_index_pos (right_len, right);
  if (min_index_pos == -2 || max_index_pos == -2) {
    return -2;
  }
  int Z[3];
  memset (Z, 0, sizeof (Z));
  tree_count (item_tree, left_len, left, right_len, right, Z);
  assert (!Z[1] && !Z[2]);
  int d = Z[0] + (max_index_pos - min_index_pos);
  if (d > limit) {
    Rmax = limit;
  } else {
    Rmax = d;
  }
  *total = d;
  int i;
  for (i = 0; i < d; i++) {
    if (i < Rmax) {
      RR[i] = i;
    } else {      
      int k = lrand48 () % (i + 1);
      if (k < Rmax) {
        RR[k] = i;
      }
    }
  }
  if (d > Rmax) {
    qsort (RR, Rmax, 4, cmp);
  }
  __array_report = array_ifwrite;
  __tree_report = tree_ifwrite;
  B = R;
  Bpos = 0;
  Bsize = size;
  Rpos = 0;
  Rt = 0;
  int r = listree_iterator (left_len, left, right_len, right, min_index_pos, max_index_pos);
  if (r == -2) { return r; }
  *cnt = Rmax;
  return (size - Bsize);
}