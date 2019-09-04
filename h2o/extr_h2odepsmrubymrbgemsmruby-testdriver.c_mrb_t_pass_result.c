#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mrb_value ;
struct TYPE_10__ {scalar_t__ exc; } ;
typedef  TYPE_1__ mrb_state ;
typedef  size_t mrb_int ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 scalar_t__ FALSE ; 
 size_t RARRAY_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * RARRAY_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RSTRING_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RSTRING_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ mrb_array_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_ary_push (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mrb_fixnum (int /*<<< orphan*/ ) ; 
 scalar_t__ mrb_fixnum_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_fixnum_value (scalar_t__) ; 
 int /*<<< orphan*/  mrb_gv_get (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_gv_set (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_intern_lit (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  mrb_print_error (TYPE_1__*) ; 
 int /*<<< orphan*/  mrb_str_new (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
mrb_t_pass_result(mrb_state *mrb_dst, mrb_state *mrb_src)
{
  mrb_value res_src;

  if (mrb_src->exc) {
    mrb_print_error(mrb_src);
    exit(EXIT_FAILURE);
  }

#define TEST_COUNT_PASS(name)                                           \
  do {                                                                  \
    res_src = mrb_gv_get(mrb_src, mrb_intern_lit(mrb_src, "$" #name));  \
    if (mrb_fixnum_p(res_src)) {                                        \
      mrb_value res_dst = mrb_gv_get(mrb_dst, mrb_intern_lit(mrb_dst, "$" #name)); \
      mrb_gv_set(mrb_dst, mrb_intern_lit(mrb_dst, "$" #name), mrb_fixnum_value(mrb_fixnum(res_dst) + mrb_fixnum(res_src))); \
    }                                                                   \
  } while (FALSE)                                                       \

  TEST_COUNT_PASS(ok_test);
  TEST_COUNT_PASS(ko_test);
  TEST_COUNT_PASS(kill_test);

#undef TEST_COUNT_PASS

  res_src = mrb_gv_get(mrb_src, mrb_intern_lit(mrb_src, "$asserts"));

  if (mrb_array_p(res_src)) {
    mrb_int i;
    mrb_value res_dst = mrb_gv_get(mrb_dst, mrb_intern_lit(mrb_dst, "$asserts"));
    for (i = 0; i < RARRAY_LEN(res_src); ++i) {
      mrb_value val_src = RARRAY_PTR(res_src)[i];
      mrb_ary_push(mrb_dst, res_dst, mrb_str_new(mrb_dst, RSTRING_PTR(val_src), RSTRING_LEN(val_src)));
    }
  }
}