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
 int /*<<< orphan*/  mrb_funcall (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_str_new_cstr (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  mrb_top_self (int /*<<< orphan*/ *) ; 

mrb_value h2o_mruby_eval_expr(mrb_state *mrb, const char *expr)
{
    return mrb_funcall(mrb, mrb_top_self(mrb), "eval", 1, mrb_str_new_cstr(mrb, expr));
}