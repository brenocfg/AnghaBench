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
typedef  int /*<<< orphan*/  OnigRegex ;

/* Variables and functions */
 int /*<<< orphan*/  Data_Get_Struct (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ONIG_OPTION_IGNORECASE ; 
 int /*<<< orphan*/  mrb_false_value () ; 
 int /*<<< orphan*/  mrb_onig_regexp_type ; 
 int /*<<< orphan*/  mrb_true_value () ; 
 int onig_get_options (int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_value
onig_regexp_casefold_p(mrb_state *mrb, mrb_value self) {
  OnigRegex reg;

  Data_Get_Struct(mrb, self, &mrb_onig_regexp_type, reg);
  return (onig_get_options(reg) & ONIG_OPTION_IGNORECASE) ? mrb_true_value() : mrb_false_value();
}