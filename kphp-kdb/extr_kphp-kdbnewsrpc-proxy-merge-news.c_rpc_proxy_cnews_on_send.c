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
struct news_gather_extra {int timestamp; int end_date; } ;
struct gather {struct news_gather_extra* extra; } ;

/* Variables and functions */
 int* Q ; 
 int* QN ; 
 int* Rfirst ; 
 int* Rlen ; 
 int TL_CNEWS_GET_RAW_UPDATES ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  tl_store_int (int) ; 

int rpc_proxy_cnews_on_send (struct gather *G, int num) {
  if (Rlen[num] <= 0) {
    return -1;
  }
  struct news_gather_extra *extra = G->extra;
  tl_store_int (TL_CNEWS_GET_RAW_UPDATES);  
  tl_store_int (extra->timestamp);
  tl_store_int (extra->end_date);
  tl_store_int (Rlen[num]);
  int x = Rfirst[num];
  int i;
  for (i = 0; i < Rlen[num]; i++) {
    assert (x >= 0);
    tl_store_int (Q[3 * x + 0]);
    tl_store_int (Q[3 * x + 1]);
    tl_store_int (Q[3 * x + 2]);
    x = QN[x];
  }
  assert (x == -1);
  return 0;
}