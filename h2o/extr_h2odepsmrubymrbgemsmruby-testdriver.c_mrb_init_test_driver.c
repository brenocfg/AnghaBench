#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct RClass {int dummy; } ;
struct TYPE_9__ {struct RClass* kernel_module; } ;
typedef  TYPE_1__ mrb_state ;
typedef  scalar_t__ mrb_bool ;

/* Variables and functions */
 int /*<<< orphan*/  MRB_ARGS_REQ (int) ; 
 int /*<<< orphan*/  MRB_INT_BIT ; 
 int /*<<< orphan*/  MRB_INT_MAX ; 
 int /*<<< orphan*/  MRB_INT_MIN ; 
 int /*<<< orphan*/  mrb_define_const (TYPE_1__*,struct RClass*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_define_method (TYPE_1__*,struct RClass*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct RClass* mrb_define_module (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  mrb_fixnum_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_float_value (TYPE_1__*,int) ; 
 int /*<<< orphan*/  mrb_gv_set (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_intern_lit (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  mrb_t_printstr ; 
 int /*<<< orphan*/  mrb_true_value () ; 

void
mrb_init_test_driver(mrb_state *mrb, mrb_bool verbose)
{
  struct RClass *krn, *mrbtest;

  krn = mrb->kernel_module;
  mrb_define_method(mrb, krn, "__t_printstr__", mrb_t_printstr, MRB_ARGS_REQ(1));

  mrbtest = mrb_define_module(mrb, "Mrbtest");

  mrb_define_const(mrb, mrbtest, "FIXNUM_MAX", mrb_fixnum_value(MRB_INT_MAX));
  mrb_define_const(mrb, mrbtest, "FIXNUM_MIN", mrb_fixnum_value(MRB_INT_MIN));
  mrb_define_const(mrb, mrbtest, "FIXNUM_BIT", mrb_fixnum_value(MRB_INT_BIT));

#ifndef MRB_WITHOUT_FLOAT
#ifdef MRB_USE_FLOAT
  mrb_define_const(mrb, mrbtest, "FLOAT_TOLERANCE", mrb_float_value(mrb, 1e-6));
#else
  mrb_define_const(mrb, mrbtest, "FLOAT_TOLERANCE", mrb_float_value(mrb, 1e-12));
#endif
#endif

  if (verbose) {
    mrb_gv_set(mrb, mrb_intern_lit(mrb, "$mrbtest_verbose"), mrb_true_value());
  }
}