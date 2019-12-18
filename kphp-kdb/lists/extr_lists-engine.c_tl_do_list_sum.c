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
struct tl_list_sum {int /*<<< orphan*/  id_ints; int /*<<< orphan*/  has_weights; int /*<<< orphan*/  count; scalar_t__ arr; int /*<<< orphan*/  mode; int /*<<< orphan*/  list_id; } ;
struct tl_act_extra {scalar_t__ extra; } ;
typedef  int /*<<< orphan*/  array_object_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  TL_LONG ; 
 long long prepare_list_sum (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tl_store_int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tl_store_long (long long) ; 

int tl_do_list_sum (struct tl_act_extra *extra) {
  struct tl_list_sum *e = (void *)(extra->extra);
  long long res = prepare_list_sum (e->list_id, e->mode, (array_object_id_t *)e->arr, e->count, e->has_weights, e->id_ints);
  if (res == -2) {
    return -2;
  }
  if (res < 0) {
    return res;
  }
  tl_store_int (TL_LONG);
  tl_store_long (res);
  return 0;
}