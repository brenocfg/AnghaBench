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
typedef  int /*<<< orphan*/  listree_t ;
typedef  int /*<<< orphan*/  list_t ;
typedef  int /*<<< orphan*/  list_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  MAXINT ; 
 int MAX_RES ; 
 int /*<<< orphan*/  OTree ; 
 scalar_t__ R ; 
 scalar_t__ R_end ; 
 int /*<<< orphan*/ * __get_list_f (int /*<<< orphan*/ ,int) ; 
 int account_date_buckets ; 
 int account_date_step ; 
 int account_max_date ; 
 int account_min_date ; 
 int /*<<< orphan*/  barray_account_date ; 
 int /*<<< orphan*/  btree_account_date ; 
 int /*<<< orphan*/  carray_account_date ; 
 scalar_t__ conv_list_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctree_account_date ; 
 int /*<<< orphan*/  in_array ; 
 int /*<<< orphan*/  in_tree ; 
 int /*<<< orphan*/  listree_get_range (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  load_o_tree_sub (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ metafile_mode ; 
 scalar_t__ prepare_list_metafile (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  unpack_metafile_pointers (int /*<<< orphan*/ *) ; 

int prepare_list_date_distr (list_id_t list_id, int mode, int min_date, int max_date, int step) {
  if (min_date <= 0 || max_date <= min_date || step <= 0 || (unsigned) mode >= 16) {
    return -1;
  }
  int rem = (max_date - min_date) % step;
  int buckets = (max_date - min_date) / step;
  if (rem || buckets > MAX_RES - 2) {
    return -1;
  }
  if (metafile_mode && prepare_list_metafile (list_id, 1) < 0) {
    return -2;
  }

  R_end = R;

  list_t *L = __get_list_f (list_id, 2);

  if (!L) {
    return conv_list_id (list_id) < 0 ? -1 : 0;
  }

  unpack_metafile_pointers (L);

  memset (R, 0, (buckets + 2) * 4);

  listree_t LI, *LT = &LI;

  if (!mode) {
    in_array = barray_account_date;
    in_tree = btree_account_date;
    LT = (listree_t *) &OTree;
  } else {
    in_array = carray_account_date;
    in_tree = ctree_account_date;
    load_o_tree_sub (LT, mode & 7);
  }
  account_min_date = min_date;
  account_max_date = max_date;
  account_date_step = step;
  account_date_buckets = buckets;
  
  listree_get_range (LT, 0, MAXINT);

  R_end = R + buckets + 2;
  
  return buckets + 2;
}