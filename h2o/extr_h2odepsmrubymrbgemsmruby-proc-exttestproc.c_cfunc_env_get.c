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
struct RProc {int dummy; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_sym ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int /*<<< orphan*/  mrb_method_t ;
typedef  int /*<<< orphan*/  mrb_int ;

/* Variables and functions */
 int /*<<< orphan*/  MRB_METHOD_FROM_PROC (int /*<<< orphan*/ ,struct RProc*) ; 
 int /*<<< orphan*/  mrb_class_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_define_method_raw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 struct RProc* mrb_proc_new_cfunc_with_env (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  return_env ; 

__attribute__((used)) static mrb_value
cfunc_env_get(mrb_state *mrb, mrb_value self)
{
  mrb_sym n;
  mrb_value *argv; mrb_int argc;
  mrb_method_t m;
  struct RProc *p;
  mrb_get_args(mrb, "na", &n, &argv, &argc);
  p = mrb_proc_new_cfunc_with_env(mrb, return_env, argc, argv);
  MRB_METHOD_FROM_PROC(m, p);
  mrb_define_method_raw(mrb, mrb_class_ptr(self), n, m);
  return self;
}