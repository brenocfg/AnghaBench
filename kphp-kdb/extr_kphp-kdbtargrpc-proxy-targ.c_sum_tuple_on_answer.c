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
 int tl_fetch_int () ; 
 int tl_fetch_unread () ; 

void sum_tuple_on_answer (struct gather *G, int num) {
  int *r = G->extra;
  if (tl_fetch_int () != r[1]) {
    return;
  } else {
    if (r[2] < 0 || r[2] == tl_fetch_int ()) {
      if (tl_fetch_unread () != r[0] * 4) { return; }
      int i;
      for (i = 0; i < r[0]; i++) {
        r[i + 3] += tl_fetch_int ();
      }
    }
  }
}