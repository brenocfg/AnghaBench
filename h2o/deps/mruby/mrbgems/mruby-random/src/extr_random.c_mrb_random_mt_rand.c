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
typedef  int /*<<< orphan*/  mt_state ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int mrb_fixnum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_fixnum_value (int) ; 
 int /*<<< orphan*/  mrb_float_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int mt_rand (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mt_rand_real (int /*<<< orphan*/ *) ; 

__attribute__((used)) static mrb_value
mrb_random_mt_rand(mrb_state *mrb, mt_state *t, mrb_value max)
{
  mrb_value value;

  if (mrb_fixnum(max) == 0) {
    value = mrb_float_value(mrb, mt_rand_real(t));
  }
  else {
    value = mrb_fixnum_value(mt_rand(t) % mrb_fixnum(max));
  }

  return value;
}