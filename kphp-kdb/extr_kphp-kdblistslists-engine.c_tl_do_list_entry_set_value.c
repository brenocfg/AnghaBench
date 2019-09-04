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
struct tl_list_entry_set_value {int /*<<< orphan*/  flags; int /*<<< orphan*/  value; int /*<<< orphan*/  object_id; int /*<<< orphan*/  list_id; } ;
struct tl_act_extra {scalar_t__ extra; } ;

/* Variables and functions */
 int /*<<< orphan*/  TL_MAYBE_FALSE ; 
 int /*<<< orphan*/  TL_MAYBE_TRUE ; 
 scalar_t__ WaitAioArrPos ; 
 long long do_change_entry_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tl_store_int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tl_store_long (long long) ; 

int tl_do_list_entry_set_value (struct tl_act_extra *extra) {
  struct tl_list_entry_set_value *e = (void *)extra->extra;
  long long res = do_change_entry_value (e->list_id, e->object_id, e->value, e->flags);
  if (res == (-1ll << 63) && WaitAioArrPos) { return -2; }
  if (res == (-1ll << 63)) {
    tl_store_int (TL_MAYBE_FALSE);
  } else {
    tl_store_int (TL_MAYBE_TRUE);
    tl_store_long (res);
  }
  return 0;
}