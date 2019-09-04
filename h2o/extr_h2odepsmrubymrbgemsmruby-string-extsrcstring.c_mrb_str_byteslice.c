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
typedef  int mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int mrb_int ;

/* Variables and functions */
 int /*<<< orphan*/  E_RANGE_ERROR ; 
 int /*<<< orphan*/  E_TYPE_ERROR ; 
#define  MRB_TT_FIXNUM 130 
#define  MRB_TT_FLOAT 129 
#define  MRB_TT_RANGE 128 
 int RSTRING_LEN (int) ; 
 int /*<<< orphan*/  TRUE ; 
 int mrb_fixnum (int) ; 
 int mrb_fixnum_value (int) ; 
 int /*<<< orphan*/  mrb_float (int) ; 
 int mrb_get_argc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,int*,int*) ; 
 int mrb_nil_value () ; 
 int /*<<< orphan*/  mrb_raise (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mrb_raisef (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mrb_range_beg_len (int /*<<< orphan*/ *,int,int*,int*,int,int /*<<< orphan*/ ) ; 
 int mrb_str_substr (int /*<<< orphan*/ *,int,int,int) ; 
 int mrb_type (int) ; 

__attribute__((used)) static mrb_value
mrb_str_byteslice(mrb_state *mrb, mrb_value str)
{
  mrb_value a1;
  mrb_int len;

  if (mrb_get_argc(mrb) == 2) {
    mrb_int pos;
    mrb_get_args(mrb, "ii", &pos, &len);
    return mrb_str_substr(mrb, str, pos, len);
  }
  mrb_get_args(mrb, "o|i", &a1, &len);
  switch (mrb_type(a1)) {
  case MRB_TT_RANGE:
    {
      mrb_int beg;

      len = RSTRING_LEN(str);
      switch (mrb_range_beg_len(mrb, a1, &beg, &len, len, TRUE)) {
      case 0:                   /* not range */
        break;
      case 1:                   /* range */
        return mrb_str_substr(mrb, str, beg, len);
      case 2:                   /* out of range */
        mrb_raisef(mrb, E_RANGE_ERROR, "%S out of range", a1);
        break;
      }
      return mrb_nil_value();
    }
#ifndef MRB_WITHOUT_FLOAT
  case MRB_TT_FLOAT:
    a1 = mrb_fixnum_value((mrb_int)mrb_float(a1));
    /* fall through */
#endif
  case MRB_TT_FIXNUM:
    return mrb_str_substr(mrb, str, mrb_fixnum(a1), 1);
  default:
    mrb_raise(mrb, E_TYPE_ERROR, "wrong type of argument");
  }
  /* not reached */
  return mrb_nil_value();
}