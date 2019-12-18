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
typedef  int mrb_int ;

/* Variables and functions */
 int /*<<< orphan*/  E_ARGUMENT_ERROR ; 
 int /*<<< orphan*/  MRB_TT_RANGE ; 
 int RARRAY_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  mrb_ary_new (int /*<<< orphan*/ *) ; 
 int mrb_fixnum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_fixnum_value (int) ; 
 int /*<<< orphan*/  mrb_funcall (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mrb_get_args (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_get_backtrace (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 
 int /*<<< orphan*/  mrb_raisef (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int mrb_range_beg_len (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_to_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_type (int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_value
mrb_f_caller(mrb_state *mrb, mrb_value self)
{
  mrb_value bt, v, length;
  mrb_int bt_len, argc, lev, n;

  bt = mrb_get_backtrace(mrb);
  bt_len = RARRAY_LEN(bt);
  argc = mrb_get_args(mrb, "|oo", &v, &length);

  switch (argc) {
    case 0:
      lev = 1;
      n = bt_len - lev;
      break;
    case 1:
      if (mrb_type(v) == MRB_TT_RANGE) {
        mrb_int beg, len;
        if (mrb_range_beg_len(mrb, v, &beg, &len, bt_len, TRUE) == 1) {
          lev = beg;
          n = len;
        }
        else {
          return mrb_nil_value();
        }
      }
      else {
        v = mrb_to_int(mrb, v);
        lev = mrb_fixnum(v);
        if (lev < 0) {
          mrb_raisef(mrb, E_ARGUMENT_ERROR, "negative level (%S)", v);
        }
        n = bt_len - lev;
      }
      break;
    case 2:
      lev = mrb_fixnum(mrb_to_int(mrb, v));
      n = mrb_fixnum(mrb_to_int(mrb, length));
      if (lev < 0) {
        mrb_raisef(mrb, E_ARGUMENT_ERROR, "negative level (%S)", v);
      }
      if (n < 0) {
        mrb_raisef(mrb, E_ARGUMENT_ERROR, "negative size (%S)", length);
      }
      break;
    default:
      lev = n = 0;
      break;
  }

  if (n == 0) {
    return mrb_ary_new(mrb);
  }

  return mrb_funcall(mrb, bt, "[]", 2, mrb_fixnum_value(lev), mrb_fixnum_value(n));
}