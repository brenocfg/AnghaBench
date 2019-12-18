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
typedef  int /*<<< orphan*/  item_t ;

/* Variables and functions */
 scalar_t__ Q_skip_mismatch_words_if_complete_case_found ; 
 int /*<<< orphan*/  clear_res () ; 
 int /*<<< orphan*/  store_res (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void priority_sort_store_res (item_t *I, int p, int *found) {
  if (Q_skip_mismatch_words_if_complete_case_found) {
    if (p >= 6) {
      if (!(*found)) {
        *found = 1;
        clear_res ();
      }
      store_res (I, p);
    } else {
      if (!(*found)) {
        store_res (I, p);
      }
    }
  } else {
    store_res (I, p);
  }
}