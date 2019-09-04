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
struct tl_list_sum {int id_ints; int count; int has_weights; scalar_t__ arr; void* mode; int /*<<< orphan*/  list_id; } ;
struct tl_act_extra {int size; scalar_t__ extra; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_LIST_OBJECT_INTS ; 
 int /*<<< orphan*/  TL_ERROR_VALUE_NOT_IN_RANGE ; 
 scalar_t__ fetch_list_id (int /*<<< orphan*/ *) ; 
 void* object_id_ints ; 
 int /*<<< orphan*/  stats_buff ; 
 struct tl_act_extra* tl_act_extra_init (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tl_do_list_sum ; 
 int /*<<< orphan*/  tl_fetch_end () ; 
 scalar_t__ tl_fetch_error () ; 
 void* tl_fetch_int () ; 
 int /*<<< orphan*/  tl_fetch_set_error_format (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ tl_fetch_string_data (char*,int) ; 

struct tl_act_extra *tl_list_sum (int is_wild, int has_weights) {
  struct tl_act_extra *extra = tl_act_extra_init (stats_buff, sizeof (struct tl_list_sum), tl_do_list_sum);
  struct tl_list_sum *e = (void *)extra->extra;

  CHECK_LIST_OBJECT_INTS;
  if (fetch_list_id (&e->list_id) < 0) {
    return 0;
  }

  e->id_ints = is_wild ? tl_fetch_int () : object_id_ints;
  e->mode = tl_fetch_int ();
  e->count = tl_fetch_int ();
  e->has_weights = has_weights;

  int bytes = 4 * (e->id_ints + (has_weights != 0));
  if (bytes * e->count > (1 << 20) || e->count < 0) {
    tl_fetch_set_error_format (TL_ERROR_VALUE_NOT_IN_RANGE, "Too long query. Total %d bytes", bytes * e->count);
    return 0;
  }
  if (tl_fetch_string_data ((char *)e->arr, bytes * e->count) < 0) {
    return 0;
  }
  extra->size += bytes * (e->count + 1);

  tl_fetch_end ();
  if (tl_fetch_error ()) {
    return 0;
  }
  return extra;  
}