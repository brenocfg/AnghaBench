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
struct RClass {int dummy; } ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  MRB_ARGS_NONE () ; 
 int /*<<< orphan*/  MRB_ARGS_REQ (int) ; 
 int /*<<< orphan*/  mrb_define_method (int /*<<< orphan*/ *,struct RClass*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_int_allbits ; 
 int /*<<< orphan*/  mrb_int_anybits ; 
 int /*<<< orphan*/  mrb_int_chr ; 
 int /*<<< orphan*/  mrb_int_nobits ; 
 struct RClass* mrb_module_get (int /*<<< orphan*/ *,char*) ; 

void
mrb_mruby_numeric_ext_gem_init(mrb_state* mrb)
{
  struct RClass *i = mrb_module_get(mrb, "Integral");

  mrb_define_method(mrb, i, "chr", mrb_int_chr, MRB_ARGS_NONE());
  mrb_define_method(mrb, i, "allbits?", mrb_int_allbits, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, i, "anybits?", mrb_int_anybits, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, i, "nobits?", mrb_int_nobits, MRB_ARGS_REQ(1));
}