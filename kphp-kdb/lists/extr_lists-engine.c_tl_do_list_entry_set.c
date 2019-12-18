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
struct tl_list_entry_set {scalar_t__ text_len; int op; int /*<<< orphan*/  text; int /*<<< orphan*/  object_id; int /*<<< orphan*/  list_id; int /*<<< orphan*/  ip; int /*<<< orphan*/  value; int /*<<< orphan*/  flags; } ;
struct tl_act_extra {scalar_t__ extra; } ;

/* Variables and functions */
 int /*<<< orphan*/  TL_BOOL_FALSE ; 
 int /*<<< orphan*/  TL_BOOL_TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int do_add_list_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int do_change_entry_text (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  tl_store_int (int /*<<< orphan*/ ) ; 

int tl_do_list_entry_set (struct tl_act_extra *extra) {
  struct tl_list_entry_set *e = (void *)extra->extra;
  int res;
  if (e->text_len < 0) {
    res = do_add_list_entry (e->list_id, e->object_id, e->op, e->flags, e->value, &e->ip);
    if (res == -2) { return -2; }
    if (res <= 0) {
      tl_store_int (TL_BOOL_FALSE);
      return 0;
    }
  } else {
    res = do_add_list_entry (e->list_id, e->object_id, e->op == 0 ? 3 : e->op , e->flags, e->value, &e->ip);
  
    if (res == -2) { return -2; }
    if (res <= 0) {
      tl_store_int (TL_BOOL_FALSE);
      return 0;
    }

    res = do_change_entry_text (e->list_id, e->object_id, e->text, e->text_len);
    assert (res >= 0);
  }

  tl_store_int (TL_BOOL_TRUE);
  return 0;
}