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
typedef  int /*<<< orphan*/  mrb_int ;
typedef  int /*<<< orphan*/  mrb_float ;

/* Variables and functions */
 long long MRB_INT_MAX ; 
 long long MRB_INT_MIN ; 
 int /*<<< orphan*/  mrb_fixnum_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_float_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_value
mrb_ll2num(mrb_state *mrb, long long t)
{
  if (MRB_INT_MIN <= t && t <= MRB_INT_MAX) {
    return mrb_fixnum_value((mrb_int)t);
  } else {
    return mrb_float_value(mrb, (mrb_float)t);
  }
}