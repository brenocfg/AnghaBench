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

/* Variables and functions */
 int /*<<< orphan*/  E_TYPE_ERROR ; 
 int /*<<< orphan*/  mrb_array_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_intern_lit (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ mrb_nil_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_obj_value (struct RClass*) ; 
 int /*<<< orphan*/  mrb_raise (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  struct_ivar_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_value
struct_s_members(mrb_state *mrb, struct RClass *klass)
{
  mrb_value members = struct_ivar_get(mrb, mrb_obj_value(klass), mrb_intern_lit(mrb, "__members__"));

  if (mrb_nil_p(members)) {
    mrb_raise(mrb, E_TYPE_ERROR, "uninitialized struct");
  }
  if (!mrb_array_p(members)) {
    mrb_raise(mrb, E_TYPE_ERROR, "corrupted struct");
  }
  return members;
}