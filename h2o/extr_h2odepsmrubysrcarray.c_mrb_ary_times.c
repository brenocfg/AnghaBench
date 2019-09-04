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
struct RArray {int dummy; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int mrb_int ;

/* Variables and functions */
 int ARY_LEN (struct RArray*) ; 
 int ARY_MAX_SIZE ; 
 int /*<<< orphan*/ * ARY_PTR (struct RArray*) ; 
 int /*<<< orphan*/  ARY_SET_LEN (struct RArray*,int) ; 
 int /*<<< orphan*/  E_ARGUMENT_ERROR ; 
 int /*<<< orphan*/  array_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct RArray* ary_new_capa (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mrb_ary_new (int /*<<< orphan*/ *) ; 
 struct RArray* mrb_ary_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,int*) ; 
 int /*<<< orphan*/  mrb_obj_value (struct RArray*) ; 
 int /*<<< orphan*/  mrb_raise (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static mrb_value
mrb_ary_times(mrb_state *mrb, mrb_value self)
{
  struct RArray *a1 = mrb_ary_ptr(self);
  struct RArray *a2;
  mrb_value *ptr;
  mrb_int times, len1;

  mrb_get_args(mrb, "i", &times);
  if (times < 0) {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "negative argument");
  }
  if (times == 0) return mrb_ary_new(mrb);
  if (ARY_MAX_SIZE / times < ARY_LEN(a1)) {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "array size too big");
  }
  len1 = ARY_LEN(a1);
  a2 = ary_new_capa(mrb, len1 * times);
  ARY_SET_LEN(a2, len1 * times);
  ptr = ARY_PTR(a2);
  while (times--) {
    array_copy(ptr, ARY_PTR(a1), len1);
    ptr += len1;
  }

  return mrb_obj_value(a2);
}