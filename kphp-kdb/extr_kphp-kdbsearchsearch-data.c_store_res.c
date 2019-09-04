#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  item_t ;
struct TYPE_5__ {int minr; int maxr; int /*<<< orphan*/  idx; } ;
struct TYPE_4__ {scalar_t__ h; scalar_t__ filled; } ;

/* Variables and functions */
 int FLAG_ENTRY_SORT_SEARCH ; 
 int FLAG_PRIORITY_SORT_SEARCH ; 
 int FLAG_REVERSE_SEARCH ; 
 scalar_t__ MAX_RATES ; 
 scalar_t__ MAX_RES ; 
 scalar_t__ Q_hash_group_mode ; 
 scalar_t__ Q_limit ; 
 int Q_order ; 
 TYPE_3__* Q_range ; 
 scalar_t__ Q_type ; 
 int /*<<< orphan*/ ** R ; 
 int* RV ; 
 scalar_t__ R_cnt ; 
 int /*<<< orphan*/  R_tot ; 
 scalar_t__ R_tot_undef_hash ; 
 int /*<<< orphan*/  add_items_into_hashset () ; 
 int /*<<< orphan*/  assert (int) ; 
 int evaluate_rating (int /*<<< orphan*/ *,int) ; 
 long long extract_hash_item (int /*<<< orphan*/ *) ; 
 int get_rate_item (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hashset_init (scalar_t__) ; 
 scalar_t__ hashset_ll_insert (TYPE_1__*,long long const) ; 
 TYPE_1__ hs ; 
 int n_ranges ; 
 int order ; 
 int /*<<< orphan*/  store_res_group_mode (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vkprintf (int,char*,int,...) ; 

__attribute__((used)) static int store_res (item_t *I, int priority) {
  vkprintf (3, "store_res!!, n_ranges = %d\n", n_ranges);
  int i, j = 0, r;
  for (i = 0; i < n_ranges; i++) {
    int r0 = get_rate_item (I, Q_range[i].idx);
    vkprintf (3, "ranges: r0 = %d, Q_range[i].minr = %d, Q_range[i].maxr = %d\n", r0, Q_range[i].minr, Q_range[i].maxr);
    if (r0 < Q_range[i].minr || r0 > Q_range[i].maxr) {
      return 1;
    }
  }

  R_tot++;
  if (Q_limit <= 0) {
    if (!Q_hash_group_mode) { return 1; }
    const long long hc = extract_hash_item (R[i]);
    if (hc != 0) {
      if (R_cnt < MAX_RES) {
        R[R_cnt++] = I;
      } else {
        if (hs.h == 0) {
          /* add found items into hashset */
          hashset_init (MAX_RES);
          add_items_into_hashset ();
        }
        if (hashset_ll_insert (&hs, hc)) {
          if (hs.filled + R_tot_undef_hash > MAX_RES) {
            /* stop search : we found too many different groups */
            return 0;
          }
        }
      }
    } else {
      R_tot_undef_hash++;
    }
    return (hs.filled + R_tot_undef_hash > MAX_RES) ? 0 : 1;
  }

  if (Q_hash_group_mode) {
    store_res_group_mode (I, priority);
    return 1;
  }

  if (Q_type == MAX_RATES && !(Q_order & (FLAG_ENTRY_SORT_SEARCH | FLAG_PRIORITY_SORT_SEARCH))) { //sort by id
    if ((Q_order & FLAG_REVERSE_SEARCH) && R_cnt == Q_limit) {
      R_cnt = 0;
    }
    if (R_cnt < Q_limit) {
      R[R_cnt++] = I;
    }
    return 1;
  }

  r = evaluate_rating (I, priority);

  if (order == 2) {
    r = -(r + 1);
  }


  assert (order != 0);

  if (R_cnt == Q_limit) {
    if (RV[1] <= r) {
      return 1;
    }
    i = 1;
    while (1) {
      j = i*2;
      if (j > R_cnt) { break; }
      if (j < R_cnt) {
        if (RV[j+1] > RV[j]) {
          j++;
        }
      }
      if (RV[j] <= r) { break; }
      R[i] = R[j];
      RV[i] = RV[j];
      i = j;
    }
    R[i] = I;
    RV[i] = r;
  } else {
    i = ++R_cnt;
    while (i > 1) {
      j = (i >> 1);
      if (RV[j] >= r) { break; }
      R[i] = R[j];
      RV[i] = RV[j];
      i = j;
    }
    R[i] = I;
    RV[i] = r;
  }
  return 1;
}