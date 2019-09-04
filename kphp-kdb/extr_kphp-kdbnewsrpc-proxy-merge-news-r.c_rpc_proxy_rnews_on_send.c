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
struct rnews_gather_extra {scalar_t__ type_mask; scalar_t__ date; scalar_t__ end_date; scalar_t__ id; scalar_t__ t; scalar_t__ timestamp; } ;
struct gather {struct rnews_gather_extra* extra; } ;

/* Variables and functions */
 scalar_t__* Q ; 
 int* QN ; 
 int /*<<< orphan*/  R ; 
 scalar_t__ R_common_len ; 
 int* Rfirst ; 
 scalar_t__* Rlen ; 
 scalar_t__ TL_NEWS_GET_RAW_UPDATES ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  tl_store_int (scalar_t__) ; 
 int /*<<< orphan*/  tl_store_raw_data (int /*<<< orphan*/ ,scalar_t__) ; 

int rpc_proxy_rnews_on_send (struct gather *G, int num) {
  if (Rlen[num] + R_common_len <= 0 ) {
    return -1;
  }
  struct rnews_gather_extra *extra = G->extra;
  tl_store_int (TL_NEWS_GET_RAW_UPDATES);  
  tl_store_int (extra->type_mask);
  tl_store_int (extra->date);
  tl_store_int (extra->end_date);
  tl_store_int (extra->id);
  tl_store_int (extra->t);
  tl_store_int (extra->timestamp);
  tl_store_int (Rlen[num] + R_common_len);
  tl_store_raw_data (R, R_common_len * 4);
  int x = Rfirst[num];
  int i;
  for (i = 0; i < Rlen[num]; i++) {
    assert (x >= 0);
    tl_store_int (Q[2 * x + 0]);
    tl_store_int (Q[2 * x + 1]);
    x = QN[x];
  }
  assert (x == -1);
  return 0;
}