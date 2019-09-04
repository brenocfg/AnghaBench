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
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 struct RObject* method_object_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_class_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mrb_intern_lit (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mrb_iv_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 
 int /*<<< orphan*/  mrb_obj_iv_set (int /*<<< orphan*/ *,struct RObject*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_obj_value (struct RObject*) ; 

__attribute__((used)) static mrb_value
method_unbind(mrb_state *mrb, mrb_value self)
{
  struct RObject *ume;
  mrb_value owner = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@owner"));
  mrb_value name = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@name"));
  mrb_value proc = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "proc"));
  mrb_value klass = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@klass"));

  ume = method_object_alloc(mrb, mrb_class_get(mrb, "UnboundMethod"));
  mrb_obj_iv_set(mrb, ume, mrb_intern_lit(mrb, "@owner"), owner);
  mrb_obj_iv_set(mrb, ume, mrb_intern_lit(mrb, "@recv"), mrb_nil_value());
  mrb_obj_iv_set(mrb, ume, mrb_intern_lit(mrb, "@name"), name);
  mrb_obj_iv_set(mrb, ume, mrb_intern_lit(mrb, "proc"), proc);
  mrb_obj_iv_set(mrb, ume, mrb_intern_lit(mrb, "@klass"), klass);

  return mrb_obj_value(ume);
}