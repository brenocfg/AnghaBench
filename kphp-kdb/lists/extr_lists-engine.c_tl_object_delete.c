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
struct tl_object_delete {int /*<<< orphan*/  object_id; } ;
struct tl_act_extra {scalar_t__ extra; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_LIST_OBJECT_INTS ; 
 int /*<<< orphan*/  delete_object_queries ; 
 scalar_t__ fetch_object_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stats_buff ; 
 struct tl_act_extra* tl_act_extra_init (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tl_do_object_delete ; 
 int /*<<< orphan*/  tl_fetch_end () ; 
 scalar_t__ tl_fetch_error () ; 

struct tl_act_extra *tl_object_delete (void) {
  struct tl_act_extra *extra = tl_act_extra_init (stats_buff, sizeof (struct tl_object_delete), tl_do_object_delete);
  struct tl_object_delete *e = (void *)extra->extra;
  CHECK_LIST_OBJECT_INTS;
  if (fetch_object_id (&e->object_id) < 0) {
    return 0;
  }
  tl_fetch_end ();
  if (tl_fetch_error ()) {
    return 0;
  }
  delete_object_queries ++; 
  return extra;
}