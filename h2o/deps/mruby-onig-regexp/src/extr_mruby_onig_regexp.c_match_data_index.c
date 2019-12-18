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
typedef  int mrb_int ;

/* Variables and functions */
#define  MRB_TT_FIXNUM 130 
#define  MRB_TT_STRING 129 
#define  MRB_TT_SYMBOL 128 
 int /*<<< orphan*/  match_data_actual_index (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  match_data_to_a (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_ary_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_funcall_argv (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  mrb_intern_lit (int /*<<< orphan*/ *,char*) ; 
 int mrb_type (int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_value
match_data_index(mrb_state* mrb, mrb_value self) {
  mrb_value src;
  mrb_int argc; mrb_value *argv;

  mrb_get_args(mrb, "*", &argv, &argc);

  src = match_data_to_a(mrb, self);

  if (argc == 1) {
    switch (mrb_type(argv[0])) {
    case MRB_TT_FIXNUM:
    case MRB_TT_SYMBOL:
    case MRB_TT_STRING:
      return mrb_ary_entry(src, match_data_actual_index(mrb, self, argv[0]));
    default: break;
    }
  }

  return mrb_funcall_argv(mrb, src, mrb_intern_lit(mrb, "[]"), argc, argv);
}