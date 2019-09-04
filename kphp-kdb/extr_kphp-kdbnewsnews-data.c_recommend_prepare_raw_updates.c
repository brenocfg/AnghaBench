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
typedef  int /*<<< orphan*/  dyn_mark_t ;

/* Variables and functions */
 int dups_users_removed_from_urlist ; 
 int /*<<< orphan*/  dyn_mark (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dyn_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  forbidden_owners_hashset ; 
 int /*<<< orphan*/  hashset_int_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hashset_int_insert (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mandatory_owners_hashset ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int now ; 
 int /*<<< orphan*/  qsort (int*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  recommend_cmp_pair1 ; 
 int /*<<< orphan*/  recommend_cmp_pair2 ; 
 int recommend_finish_raw_updates (int) ; 
 int /*<<< orphan*/  recommend_init_raw_updates () ; 
 int /*<<< orphan*/  recommend_process_raw_updates (int,int,int,int,int,int,int const) ; 

int recommend_prepare_raw_updates (int *Q, int QL, int mask, int st_time, int end_time, int excluded_user_id, int timestamp, int T) {
  int i, mandatory_owners = 0, forbidden_owners = 1;
  dyn_mark_t mrk;
  dyn_mark (mrk);
  for (i = 0; i < QL; i++) {
    if (Q[(i<<1)+1] == -2) {
      mandatory_owners++;
    } else if (Q[(i<<1)+1] == -1) {
      forbidden_owners++;
    }
  }
  hashset_int_init (&mandatory_owners_hashset, mandatory_owners);
  hashset_int_init (&forbidden_owners_hashset, forbidden_owners);
  for (i = 0; i < QL; ) {
    if (Q[(i<<1)+1] == -2) {
      hashset_int_insert (&mandatory_owners_hashset, Q[i<<1]);
      QL--;
      if (i != QL) {
        memcpy (Q + (i<<1), Q + (QL<<1), 8);
      }
      continue;
    } else if (Q[(i<<1)+1] == -1) {
      hashset_int_insert (&forbidden_owners_hashset, Q[i<<1]);
      QL--;
      if (i != QL) {
        memcpy (Q + (i<<1), Q + (QL<<1), 8);
      }
      continue;
    }
    i++;
  }
  hashset_int_insert (&forbidden_owners_hashset, excluded_user_id);

  /* remove duplicate users */
  int m = 0;
  qsort (Q, QL, 8, recommend_cmp_pair1);
  for (i = 1; i < QL; i++) {
    if (Q[2*i] != Q[2*m]) {
      ++m;
      Q[2*m] = Q[2*i];
      Q[2*m+1] = Q[2*i+1];
    }
  }
  m++;
  dups_users_removed_from_urlist += QL - m;
  QL = m;
  /* sort in rating decreasing order */
  qsort (Q, QL, 8, recommend_cmp_pair2);

  const int min_item_creation_time = now - 30 * T;
  recommend_init_raw_updates ();
  for (i = 0; i < QL; i++) {
    recommend_process_raw_updates (Q[(i<<1)], Q[(i<<1)+1], mask, st_time, end_time, timestamp, min_item_creation_time);
  }
  int res = recommend_finish_raw_updates (T);
  dyn_release (mrk);
  return res;
}