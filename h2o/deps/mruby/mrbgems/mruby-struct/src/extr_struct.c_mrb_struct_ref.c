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
typedef  size_t mrb_int ;

/* Variables and functions */
 int /*<<< orphan*/ * RSTRUCT_PTR (int /*<<< orphan*/ ) ; 
 size_t mrb_fixnum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 
 int /*<<< orphan*/  mrb_proc_cfunc_env_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_value
mrb_struct_ref(mrb_state *mrb, mrb_value obj)
{
  mrb_int i = mrb_fixnum(mrb_proc_cfunc_env_get(mrb, 0));
  mrb_value *ptr = RSTRUCT_PTR(obj);

  if (!ptr) return mrb_nil_value();
  return ptr[i];
}