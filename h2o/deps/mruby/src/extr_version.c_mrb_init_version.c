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
 int /*<<< orphan*/  MRUBY_COPYRIGHT ; 
 int /*<<< orphan*/  MRUBY_DESCRIPTION ; 
 int /*<<< orphan*/  MRUBY_RELEASE_DATE ; 
 int /*<<< orphan*/  MRUBY_RELEASE_NO ; 
 int /*<<< orphan*/  MRUBY_RUBY_ENGINE ; 
 int /*<<< orphan*/  MRUBY_RUBY_VERSION ; 
 int /*<<< orphan*/  MRUBY_VERSION ; 
 int /*<<< orphan*/  mrb_define_global_const (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_fixnum_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_str_new_lit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
mrb_init_version(mrb_state* mrb)
{
  mrb_value mruby_version = mrb_str_new_lit(mrb, MRUBY_VERSION);

  mrb_define_global_const(mrb, "RUBY_VERSION", mrb_str_new_lit(mrb, MRUBY_RUBY_VERSION));
  mrb_define_global_const(mrb, "RUBY_ENGINE", mrb_str_new_lit(mrb, MRUBY_RUBY_ENGINE));
  mrb_define_global_const(mrb, "RUBY_ENGINE_VERSION", mruby_version);
  mrb_define_global_const(mrb, "MRUBY_VERSION", mruby_version);
  mrb_define_global_const(mrb, "MRUBY_RELEASE_NO", mrb_fixnum_value(MRUBY_RELEASE_NO));
  mrb_define_global_const(mrb, "MRUBY_RELEASE_DATE", mrb_str_new_lit(mrb, MRUBY_RELEASE_DATE));
  mrb_define_global_const(mrb, "MRUBY_DESCRIPTION", mrb_str_new_lit(mrb, MRUBY_DESCRIPTION));
  mrb_define_global_const(mrb, "MRUBY_COPYRIGHT", mrb_str_new_lit(mrb, MRUBY_COPYRIGHT));
}