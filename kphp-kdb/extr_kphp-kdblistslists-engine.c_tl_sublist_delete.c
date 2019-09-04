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
struct tl_sublist_delete {int xor_mask; int and_mask; int /*<<< orphan*/  list_id; } ;
struct tl_act_extra {scalar_t__ extra; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_LIST_OBJECT_INTS ; 
 scalar_t__ fetch_list_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stats_buff ; 
 struct tl_act_extra* tl_act_extra_init (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tl_do_sublist_delete ; 
 int /*<<< orphan*/  tl_fetch_end () ; 
 scalar_t__ tl_fetch_error () ; 
 int tl_fetch_int () ; 

struct tl_act_extra *tl_sublist_delete (int ex) {
  struct tl_act_extra *extra = tl_act_extra_init (stats_buff, sizeof (struct tl_sublist_delete), tl_do_sublist_delete);
  struct tl_sublist_delete *e = (void *)extra->extra;
  CHECK_LIST_OBJECT_INTS;
  if (fetch_list_id (&e->list_id) < 0) {
    return 0;
  }
  
  e->xor_mask = tl_fetch_int ();
  e->and_mask = ex ? tl_fetch_int () : 7;

  tl_fetch_end ();
  if (tl_fetch_error ()) {
    return 0;
  }

  return extra;
}