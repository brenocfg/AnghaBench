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
struct RObject {int dummy; } ;
struct RClass {int dummy; } ;
typedef  int /*<<< orphan*/  mrb_sym ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  mrb_class_name_class (int /*<<< orphan*/ *,struct RClass*,struct RClass*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_obj_iv_set (int /*<<< orphan*/ *,struct RObject*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_obj_value (struct RClass*) ; 

__attribute__((used)) static void
setup_class(mrb_state *mrb, struct RClass *outer, struct RClass *c, mrb_sym id)
{
  mrb_class_name_class(mrb, outer, c, id);
  mrb_obj_iv_set(mrb, (struct RObject*)outer, id, mrb_obj_value(c));
}