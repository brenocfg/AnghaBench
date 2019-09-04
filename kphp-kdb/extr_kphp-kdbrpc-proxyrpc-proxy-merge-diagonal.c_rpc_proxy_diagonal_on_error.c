#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct gather {int* extra; } ;
struct TYPE_2__ {int /*<<< orphan*/  h; } ;

/* Variables and functions */
 TYPE_1__* CQ ; 
 scalar_t__ TL_IS_USER_ERROR (int) ; 
 int /*<<< orphan*/  free (int*) ; 
 scalar_t__ merge_init_response (struct gather*) ; 
 int /*<<< orphan*/  merge_terminate_gather (struct gather*) ; 
 int /*<<< orphan*/  tl_copy_through (int /*<<< orphan*/ ,int) ; 
 int tl_fetch_lookup_int () ; 
 int /*<<< orphan*/  tl_fetch_unread () ; 
 int /*<<< orphan*/  tl_store_end () ; 
 int /*<<< orphan*/  tl_store_header (int /*<<< orphan*/ ) ; 

void rpc_proxy_diagonal_on_error (struct gather *G, int num) {
  int error_code = tl_fetch_lookup_int ();
  if (TL_IS_USER_ERROR (error_code)) {
    if (merge_init_response (G) >= 0) {
      tl_store_header (CQ->h);
      tl_copy_through (tl_fetch_unread (), 1);
      tl_store_end ();
    }
    free (G->extra);
    merge_terminate_gather (G);
  } else {
    int *extra = G->extra;
    extra[2] ++;
  }
}