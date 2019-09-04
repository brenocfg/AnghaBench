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
struct tl_list_entry_set_text {int /*<<< orphan*/  len; int /*<<< orphan*/  text; int /*<<< orphan*/  object_id; int /*<<< orphan*/  list_id; } ;
struct tl_act_extra {scalar_t__ extra; } ;

/* Variables and functions */
 int /*<<< orphan*/  TL_BOOL_FALSE ; 
 int /*<<< orphan*/  TL_BOOL_TRUE ; 
 int do_change_entry_text (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tl_store_int (int /*<<< orphan*/ ) ; 

int tl_do_list_entry_set_text (struct tl_act_extra *extra) {  
  struct tl_list_entry_set_text *e = (void *)extra->extra;
  int res = do_change_entry_text (e->list_id, e->object_id, e->text, e->len);
  if (res == -2) { return -2; }
  tl_store_int (res <= 0 ? TL_BOOL_FALSE : TL_BOOL_TRUE);
  return 0;
}