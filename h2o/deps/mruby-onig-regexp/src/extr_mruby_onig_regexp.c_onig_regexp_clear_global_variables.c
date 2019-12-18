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
 int /*<<< orphan*/  mrb_gv_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_intern (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  mrb_intern_lit (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static mrb_value
onig_regexp_clear_global_variables(mrb_state* mrb, mrb_value self) {
  mrb_gv_remove(mrb, mrb_intern_lit(mrb, "$~"));
  mrb_gv_remove(mrb, mrb_intern_lit(mrb, "$&"));
  mrb_gv_remove(mrb, mrb_intern_lit(mrb, "$`"));
  mrb_gv_remove(mrb, mrb_intern_lit(mrb, "$'"));
  mrb_gv_remove(mrb, mrb_intern_lit(mrb, "$+"));

  int idx;
  for(idx = 1; idx < 10; ++idx) {
    char const n[] = { '$', '0' + idx };
    mrb_gv_remove(mrb, mrb_intern(mrb, n, 2));
  }

  return self;
}