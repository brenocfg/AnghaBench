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
struct gather {scalar_t__ extra; } ;

/* Variables and functions */
 long TL_MAYBE_TRUE ; 
 int /*<<< orphan*/  merge_delete (struct gather*) ; 
 scalar_t__ merge_init_response (struct gather*) ; 
 int /*<<< orphan*/  tl_store_end () ; 
 int /*<<< orphan*/  tl_store_int (long) ; 

void sum_one_on_end (struct gather *G) {
  if (merge_init_response (G) >= 0) {
    tl_store_int (TL_MAYBE_TRUE);
    tl_store_int (((long)G->extra) - 1);
    tl_store_end ();
  }
  merge_delete (G);
}