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
 int /*<<< orphan*/  mrb_bug (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_string_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_sym2str (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_symbol (int /*<<< orphan*/ ) ; 
 scalar_t__ mrb_symbol_p (int /*<<< orphan*/ ) ; 
 scalar_t__ mrb_undef_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_value
reg_operand(mrb_state *mrb, mrb_value obj) {
  mrb_value ret;

  if (mrb_symbol_p(obj)) {
    ret = mrb_sym2str(mrb, mrb_symbol(obj));
    if (mrb_undef_p(ret)) {
      mrb_bug(mrb, "can not intern %S", obj);
    }
  }
  else {
    ret = mrb_string_type(mrb, obj);
  }
  return ret;
}