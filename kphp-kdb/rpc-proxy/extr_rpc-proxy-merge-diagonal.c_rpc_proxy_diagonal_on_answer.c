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
struct gather {int* extra; } ;

/* Variables and functions */
 scalar_t__ TL_BOOL_STAT ; 
 scalar_t__ tl_fetch_int () ; 
 int tl_fetch_unread () ; 

void rpc_proxy_diagonal_on_answer (struct gather *G, int num) {
  int *extra = G->extra;
  if (tl_fetch_int () != TL_BOOL_STAT) {
    extra[2] ++;
    return;
  }
  if (tl_fetch_unread () != 12) {
    extra[2] ++;
    return;
  }
  extra[0] += tl_fetch_int ();
  extra[1] += tl_fetch_int ();
  extra[2] += tl_fetch_int ();
}