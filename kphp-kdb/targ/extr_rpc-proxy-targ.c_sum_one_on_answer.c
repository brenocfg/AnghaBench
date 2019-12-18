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
struct gather {void* extra; } ;

/* Variables and functions */
 int TL_MAYBE_TRUE ; 
 int tl_fetch_int () ; 

void sum_one_on_answer (struct gather *G, int num) {
  if (tl_fetch_int () != TL_MAYBE_TRUE) {
    return;
  }
  int x = tl_fetch_int ();
  G->extra = (void *)(x + (long)G->extra);
}