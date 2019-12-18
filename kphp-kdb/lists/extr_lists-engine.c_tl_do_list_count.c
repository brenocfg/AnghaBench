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
struct tl_list_count {int /*<<< orphan*/  cnt; int /*<<< orphan*/  list_id; } ;
struct tl_act_extra {scalar_t__ extra; } ;

/* Variables and functions */
 int TL_INT ; 
 int get_list_counter (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tl_store_int (int) ; 

int tl_do_list_count (struct tl_act_extra *extra) {
  struct tl_list_count *e = (void *)(extra->extra);
  int res = get_list_counter (e->list_id, e->cnt);
  if (res == -2) { return -2; }
  //if (res < 0) { return res; }
  tl_store_int (TL_INT);
  tl_store_int (res >= 0 ? res : 0);
  return 0;
}