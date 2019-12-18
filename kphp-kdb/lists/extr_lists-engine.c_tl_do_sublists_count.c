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
struct tl_list_count {int /*<<< orphan*/  list_id; } ;
struct tl_act_extra {scalar_t__ extra; } ;

/* Variables and functions */
 int /*<<< orphan*/ * R ; 
 int /*<<< orphan*/  TL_TUPLE ; 
 int fetch_list_counters (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tl_store_int (int /*<<< orphan*/ ) ; 

int tl_do_sublists_count (struct tl_act_extra *extra) {
  struct tl_list_count *e = (void *)(extra->extra);
  int res = fetch_list_counters (e->list_id, R);
  if (res == -2) { return -2; }
  if (res < 0) { return res; }
  if (res > 9) { res = 9; }
  int i;
  tl_store_int (TL_TUPLE);
  for (i = 0; i < res; i++) {
    tl_store_int (R[i]);
  }
  for (i = res; i < 9; i++) {
    tl_store_int (0);
  }
  return 0;
}