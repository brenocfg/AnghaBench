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
struct tl_list_set_flags {int xor_mask; int and_mask; int or_mask; int nand_mask; int /*<<< orphan*/  list_id; } ;
struct tl_act_extra {scalar_t__ extra; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_LIST_OBJECT_INTS ; 
 scalar_t__ fetch_list_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stats_buff ; 
 struct tl_act_extra* tl_act_extra_init (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tl_do_list_set_flags ; 
 int /*<<< orphan*/  tl_fetch_end () ; 
 scalar_t__ tl_fetch_error () ; 
 int tl_fetch_int () ; 

struct tl_act_extra *tl_list_set_flags (int type) {
  struct tl_act_extra *extra = tl_act_extra_init (stats_buff, sizeof (struct tl_list_set_flags), tl_do_list_set_flags);
  struct tl_list_set_flags *e = (void *)extra->extra;
  CHECK_LIST_OBJECT_INTS;
  if (fetch_list_id (&e->list_id) < 0) {
    return 0;
  }

  e->xor_mask = tl_fetch_int ();
  e->and_mask = type == 2 ? tl_fetch_int () : 7;
  e->or_mask = tl_fetch_int ();
  e->nand_mask = type != 0 ? tl_fetch_int () : -1;

  tl_fetch_end ();
  if (tl_fetch_error ()) {
    return 0;
  }
  return extra;
}