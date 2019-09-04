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
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  E_TYPE_ERROR ; 
 scalar_t__ RARRAY_LEN (int /*<<< orphan*/ ) ; 
 scalar_t__ RSTRUCT_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_array_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_ary_resize (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mrb_fixnum_value (scalar_t__) ; 
 int /*<<< orphan*/  mrb_obj_class (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_raise (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mrb_raisef (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  struct_s_members (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_value
struct_members(mrb_state *mrb, mrb_value s)
{
  mrb_value members = struct_s_members(mrb, mrb_obj_class(mrb, s));
  if (!mrb_array_p(s)) {
    mrb_raise(mrb, E_TYPE_ERROR, "corrupted struct");
  }
  if (RSTRUCT_LEN(s) != RARRAY_LEN(members)) {
    if (RSTRUCT_LEN(s) == 0) {  /* probably uninitialized */
      mrb_ary_resize(mrb, s, RARRAY_LEN(members));
    }
    else {
      mrb_raisef(mrb, E_TYPE_ERROR,
                 "struct size differs (%S required %S given)",
                 mrb_fixnum_value(RARRAY_LEN(members)), mrb_fixnum_value(RSTRUCT_LEN(s)));
    }
  }
  return members;
}