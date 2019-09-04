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
 int TL_BOOL_STAT ; 
 int /*<<< orphan*/  assert (int) ; 
 int do_delete_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tl_store_int (int) ; 

int tl_do_object_delete (struct tl_act_extra *extra) {
  struct tl_object_delete *e = (void *)extra->extra;
  int res = do_delete_object (e->object_id);
  assert (res != -2);
  tl_store_int (TL_BOOL_STAT);
  tl_store_int (res > 0);
  tl_store_int (res <= 0);
  tl_store_int (0);
  return 0;
}