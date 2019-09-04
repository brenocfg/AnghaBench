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
typedef  enum mrb_vtype { ____Placeholder_mrb_vtype } mrb_vtype ;

/* Variables and functions */
 int /*<<< orphan*/  E_ARGUMENT_ERROR ; 
 int MRB_TT_FIXNUM ; 
 int MRB_TT_FLOAT ; 
 int /*<<< orphan*/  mrb_funcall (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ mrb_nil_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_raise (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int mrb_type (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
r_check(mrb_state *mrb, mrb_value a, mrb_value b)
{
  mrb_value ans;
  enum mrb_vtype ta;
  enum mrb_vtype tb;

  ta = mrb_type(a);
  tb = mrb_type(b);
#ifdef MRB_WITHOUT_FLOAT
  if (ta == MRB_TT_FIXNUM && tb == MRB_TT_FIXNUM ) {
#else
  if ((ta == MRB_TT_FIXNUM || ta == MRB_TT_FLOAT) &&
      (tb == MRB_TT_FIXNUM || tb == MRB_TT_FLOAT)) {
#endif
    return;
  }

  ans =  mrb_funcall(mrb, a, "<=>", 1, b);
  if (mrb_nil_p(ans)) {
    /* can not be compared */
    mrb_raise(mrb, E_ARGUMENT_ERROR, "bad value for range");
  }
}