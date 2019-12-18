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
struct tl_list_entry_set_text {scalar_t__ len; int /*<<< orphan*/  text; int /*<<< orphan*/  object_id; int /*<<< orphan*/  list_id; } ;
struct tl_act_extra {int /*<<< orphan*/  size; scalar_t__ extra; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_LIST_OBJECT_INTS ; 
 scalar_t__ fetch_list_id (int /*<<< orphan*/ *) ; 
 scalar_t__ fetch_object_id (int /*<<< orphan*/ *) ; 
 scalar_t__ max_text_len ; 
 int /*<<< orphan*/  stats_buff ; 
 struct tl_act_extra* tl_act_extra_init (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tl_do_list_entry_set_text ; 
 int /*<<< orphan*/  tl_fetch_end () ; 
 scalar_t__ tl_fetch_error () ; 
 scalar_t__ tl_fetch_string0 (int /*<<< orphan*/ ,scalar_t__) ; 

struct tl_act_extra *tl_list_entry_set_text (void) {
  struct tl_act_extra *extra = tl_act_extra_init (stats_buff, sizeof (struct tl_list_entry_set_text), tl_do_list_entry_set_text);
  struct tl_list_entry_set_text *e = (void *)extra->extra;
  CHECK_LIST_OBJECT_INTS;
  if (fetch_list_id (&e->list_id) < 0) {
    return 0;
  }
  if (fetch_object_id (&e->object_id) < 0) {
    return 0;
  }

  e->len = tl_fetch_string0 (e->text, max_text_len - 1);
  extra->size += e->len + 1;
  tl_fetch_end ();
  if (tl_fetch_error ()) {
    return 0;
  }
  return extra;
}