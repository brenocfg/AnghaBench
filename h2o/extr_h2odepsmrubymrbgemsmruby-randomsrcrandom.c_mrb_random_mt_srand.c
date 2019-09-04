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
typedef  scalar_t__ mrb_int ;

/* Variables and functions */
 scalar_t__ mrb_fixnum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_fixnum_value (scalar_t__) ; 
 scalar_t__ mrb_nil_p (int /*<<< orphan*/ ) ; 
 scalar_t__ mt_rand (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mt_srand (int /*<<< orphan*/ *,unsigned int) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static mrb_value
mrb_random_mt_srand(mrb_state *mrb, mt_state *t, mrb_value seed)
{
  if (mrb_nil_p(seed)) {
    seed = mrb_fixnum_value((mrb_int)(time(NULL) + mt_rand(t)));
    if (mrb_fixnum(seed) < 0) {
      seed = mrb_fixnum_value(0 - mrb_fixnum(seed));
    }
  }

  mt_srand(t, (unsigned) mrb_fixnum(seed));

  return seed;
}