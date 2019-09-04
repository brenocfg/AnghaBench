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
struct mrb_md {int dummy; } ;
struct RClass {int dummy; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 scalar_t__ DATA_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_NOTIMP_ERROR ; 
 int /*<<< orphan*/  E_RUNTIME_ERROR ; 
 int /*<<< orphan*/  TYPESYM ; 
 int /*<<< orphan*/  mrb_const_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_intern_lit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ mrb_nil_p (int /*<<< orphan*/ ) ; 
 struct RClass* mrb_obj_class (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_obj_value (struct RClass*) ; 
 int /*<<< orphan*/  mrb_raise (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
basecheck(mrb_state *mrb, mrb_value self, struct mrb_md **mdp)
{
  struct RClass *c;
  struct mrb_md *md;
  mrb_value t;

  c = mrb_obj_class(mrb, self);
  t = mrb_const_get(mrb, mrb_obj_value(c), mrb_intern_lit(mrb, TYPESYM));
  if (mrb_nil_p(t)) {
    mrb_raise(mrb, E_NOTIMP_ERROR, "Digest::Base is an abstract class");
  }
  md = (struct mrb_md *)DATA_PTR(self);
  if (!md) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "no md found (BUG?)");
  }
  if (mdp) *mdp = md;
}