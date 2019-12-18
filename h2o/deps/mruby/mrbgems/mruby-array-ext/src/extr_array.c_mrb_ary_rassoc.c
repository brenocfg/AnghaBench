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
typedef  size_t mrb_int ;

/* Variables and functions */
 scalar_t__ MRB_TT_ARRAY ; 
 int RARRAY_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * RARRAY_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ mrb_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 
 scalar_t__ mrb_type (int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_value
mrb_ary_rassoc(mrb_state *mrb, mrb_value ary)
{
  mrb_int i;
  mrb_value v, value;

  mrb_get_args(mrb, "o", &value);

  for (i = 0; i < RARRAY_LEN(ary); ++i) {
    v = RARRAY_PTR(ary)[i];
    if (mrb_type(v) == MRB_TT_ARRAY &&
        RARRAY_LEN(v) > 1 &&
        mrb_equal(mrb, RARRAY_PTR(v)[1], value))
      return v;
  }
  return mrb_nil_value();
}