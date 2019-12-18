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
 int /*<<< orphan*/  lshift (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 scalar_t__ mrb_fixnum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,scalar_t__*) ; 
 int /*<<< orphan*/  rshift (scalar_t__,scalar_t__) ; 

__attribute__((used)) static mrb_value
fix_lshift(mrb_state *mrb, mrb_value x)
{
  mrb_int width, val;

  mrb_get_args(mrb, "i", &width);
  if (width == 0) {
    return x;
  }
  val = mrb_fixnum(x);
  if (val == 0) return x;
  if (width < 0) {
    return rshift(val, -width);
  }
  return lshift(mrb, val, width);
}