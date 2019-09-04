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
struct RClass {int mt; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_sym ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  scalar_t__ khiter_t ;

/* Variables and functions */
 int /*<<< orphan*/  MRB_CLASS_ORIGIN (struct RClass*) ; 
 int h ; 
 int /*<<< orphan*/  kh_del (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,scalar_t__) ; 
 scalar_t__ kh_end (int) ; 
 scalar_t__ kh_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int khash_t (int /*<<< orphan*/ ) ; 
 struct RClass* mrb_class_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_funcall (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_name_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_sym2str (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_symbol_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt ; 

__attribute__((used)) static void
remove_method(mrb_state *mrb, mrb_value mod, mrb_sym mid)
{
  struct RClass *c = mrb_class_ptr(mod);
  khash_t(mt) *h;
  khiter_t k;

  MRB_CLASS_ORIGIN(c);
  h = c->mt;

  if (h) {
    k = kh_get(mt, mrb, h, mid);
    if (k != kh_end(h)) {
      kh_del(mt, mrb, h, k);
      mrb_funcall(mrb, mod, "method_removed", 1, mrb_symbol_value(mid));
      return;
    }
  }

  mrb_name_error(mrb, mid, "method '%S' not defined in %S",
                 mrb_sym2str(mrb, mid), mod);
}