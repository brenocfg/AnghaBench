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
 int /*<<< orphan*/  merge_delete (struct gather*) ; 
 scalar_t__ merge_init_response (struct gather*) ; 
 int /*<<< orphan*/  tl_store_end () ; 
 int /*<<< orphan*/  tl_store_int (int) ; 
 int /*<<< orphan*/  tl_store_raw_data (int*,int) ; 
 int /*<<< orphan*/  zfree (int*,int) ; 

void sum_tuple_on_end (struct gather *G) {
  int *r = G->extra;
  if (merge_init_response (G) >= 0) {
    tl_store_int (r[1]);
    if (r[2] >= 0) {
      tl_store_int (r[2]);
    }
    tl_store_raw_data (r + 3, r[0] * 4);
    tl_store_end ();
  }
  zfree (r, 4 * r[0] + 12);
  merge_delete (G);
}