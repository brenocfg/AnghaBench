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
struct gather {int* extra; scalar_t__ not_sent_num; scalar_t__ timeouted_num; } ;

/* Variables and functions */
 int TL_BOOL_STAT ; 
 int /*<<< orphan*/  free (int*) ; 
 int /*<<< orphan*/  merge_delete (struct gather*) ; 
 scalar_t__ merge_init_response (struct gather*) ; 
 int /*<<< orphan*/  tl_store_end () ; 
 int /*<<< orphan*/  tl_store_int (int) ; 

void rpc_proxy_diagonal_on_end (struct gather *G) {
  int *extra = G->extra;
  if (merge_init_response (G) >= 0) {
    extra[2] += G->timeouted_num + G->not_sent_num;
    tl_store_int (TL_BOOL_STAT);
    tl_store_int (extra[0]);
    tl_store_int (extra[1]);
    tl_store_int (extra[2]);
    tl_store_end ();
  }
  free (extra);
  merge_delete (G);
}