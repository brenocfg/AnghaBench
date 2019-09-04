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
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  size_t mrb_int ;

/* Variables and functions */
 int /*<<< orphan*/  E_ARGUMENT_ERROR ; 
 int /*<<< orphan*/  mrb_ary_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 
 struct RClass* mrb_obj_class (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_raise (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 size_t num_members (int /*<<< orphan*/ *,struct RClass*) ; 

__attribute__((used)) static mrb_value
mrb_struct_initialize_withArg(mrb_state *mrb, mrb_int argc, mrb_value *argv, mrb_value self)
{
  struct RClass *klass = mrb_obj_class(mrb, self);
  mrb_int i, n;

  n = num_members(mrb, klass);
  if (n < argc) {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "struct size differs");
  }

  for (i = 0; i < argc; i++) {
    mrb_ary_set(mrb, self, i, argv[i]);
  }
  for (i = argc; i < n; i++) {
    mrb_ary_set(mrb, self, i, mrb_nil_value());
  }
  return self;
}