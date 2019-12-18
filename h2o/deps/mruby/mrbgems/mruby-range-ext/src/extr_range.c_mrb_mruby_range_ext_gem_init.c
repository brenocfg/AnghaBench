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
 int /*<<< orphan*/  MRB_ARGS_OPT (int) ; 
 int /*<<< orphan*/  MRB_ARGS_REQ (int) ; 
 struct RClass* mrb_class_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mrb_define_method (int /*<<< orphan*/ *,struct RClass*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  range_cover ; 
 int /*<<< orphan*/  range_last ; 
 int /*<<< orphan*/  range_size ; 

void
mrb_mruby_range_ext_gem_init(mrb_state* mrb)
{
  struct RClass * s = mrb_class_get(mrb, "Range");

  mrb_define_method(mrb, s, "cover?", range_cover, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, s, "last",   range_last,  MRB_ARGS_OPT(1));
  mrb_define_method(mrb, s, "size",   range_size,  MRB_ARGS_NONE());
}