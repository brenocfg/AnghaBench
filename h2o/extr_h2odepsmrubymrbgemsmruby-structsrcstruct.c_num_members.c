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
typedef  int /*<<< orphan*/  mrb_int ;

/* Variables and functions */
 int /*<<< orphan*/  E_TYPE_ERROR ; 
 int /*<<< orphan*/  RARRAY_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_array_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_intern_lit (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mrb_obj_value (struct RClass*) ; 
 int /*<<< orphan*/  mrb_raise (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  struct_ivar_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_int
num_members(mrb_state *mrb, struct RClass *klass)
{
  mrb_value members;

  members = struct_ivar_get(mrb, mrb_obj_value(klass), mrb_intern_lit(mrb, "__members__"));
  if (!mrb_array_p(members)) {
    mrb_raise(mrb, E_TYPE_ERROR, "broken members");
  }
  return RARRAY_LEN(members);
}