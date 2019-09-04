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
struct tl_list_delete {int /*<<< orphan*/  list_id; } ;
struct tl_act_extra {scalar_t__ extra; } ;

/* Variables and functions */
 int /*<<< orphan*/  TL_BOOL_FALSE ; 
 int /*<<< orphan*/  TL_BOOL_TRUE ; 
 int do_delete_list (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tl_store_int (int /*<<< orphan*/ ) ; 

int tl_do_list_delete (struct tl_act_extra *extra) {
  struct tl_list_delete *e = (void *)extra->extra;
  int res = do_delete_list (e->list_id);
  if (res == -2) { return -2; }
  tl_store_int (res <= 0 ? TL_BOOL_FALSE : TL_BOOL_TRUE);
  return 0;
}