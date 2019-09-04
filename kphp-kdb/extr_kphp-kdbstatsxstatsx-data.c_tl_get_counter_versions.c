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
struct counter {struct counter* prev; int /*<<< orphan*/  created_at; } ;

/* Variables and functions */
 int /*<<< orphan*/  TL_MAYBE_FALSE ; 
 int /*<<< orphan*/  TL_MAYBE_TRUE ; 
 struct counter* get_counter_f (long long,int /*<<< orphan*/ ) ; 
 int load_counter (long long,int /*<<< orphan*/ ,int) ; 
 int* tl_store_get_ptr (int) ; 
 int /*<<< orphan*/  tl_store_int (int /*<<< orphan*/ ) ; 

int tl_get_counter_versions (long long counter_id) {
  if (load_counter (counter_id, 0, 1) == -2) {
    return -2;
  }
  struct counter *C = get_counter_f (counter_id, 0);
  if (!C) {
    tl_store_int (TL_MAYBE_FALSE);
    return 0;
  }
  tl_store_int (TL_MAYBE_TRUE);
  int *count = tl_store_get_ptr (4);
  *count = 0;
  while (C) {
    tl_store_int (C->created_at);
    (*count) ++;
    C = C->prev;
  }
  return 0;
}