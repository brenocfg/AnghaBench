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
typedef  scalar_t__ mrb_int ;

/* Variables and functions */
 scalar_t__ mrb_fixnum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_fixnum_value (scalar_t__) ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_nil_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 
 int /*<<< orphan*/  mrb_to_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_value
get_opt(mrb_state* mrb)
{
  mrb_value arg;

  arg = mrb_nil_value();
  mrb_get_args(mrb, "|o", &arg);

  if (!mrb_nil_p(arg)) {
    mrb_int i;

    arg = mrb_to_int(mrb, arg);
    i = mrb_fixnum(arg);
    if (i < 0) {
      arg = mrb_fixnum_value(0 - i);
    }
  }
  return arg;
}