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
typedef  scalar_t__ u_char ;
typedef  int /*<<< orphan*/  FPU_REG ;

/* Variables and functions */
 scalar_t__ FPU_Special (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FPU_settag0 (scalar_t__) ; 
 int /*<<< orphan*/  FPU_to_exp16 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SIGN_POS ; 
 scalar_t__ TAG_Special ; 
 scalar_t__ TAG_Valid ; 
 scalar_t__ TAG_Zero ; 
 scalar_t__ TW_Denormal ; 
 scalar_t__ TW_Infinity ; 
 int /*<<< orphan*/  addexponent (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  arith_invalid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_C1 () ; 
 int /*<<< orphan*/  control_word ; 
 scalar_t__ denormal_operand () ; 
 int exponent (int /*<<< orphan*/ *) ; 
 int exponent16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setexponent16 (int /*<<< orphan*/ *,int) ; 
 scalar_t__ signnegative (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  single_arg_error (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ wm_sqrt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fsqrt_(FPU_REG *st0_ptr, u_char st0_tag)
{
	int expon;

	clear_C1();

	if (st0_tag == TAG_Valid) {
		u_char tag;

		if (signnegative(st0_ptr)) {
			arith_invalid(0);	/* sqrt(negative) is invalid */
			return;
		}

		/* make st(0) in  [1.0 .. 4.0) */
		expon = exponent(st0_ptr);

	      denormal_arg:

		setexponent16(st0_ptr, (expon & 1));

		/* Do the computation, the sign of the result will be positive. */
		tag = wm_sqrt(st0_ptr, 0, 0, control_word, SIGN_POS);
		addexponent(st0_ptr, expon >> 1);
		FPU_settag0(tag);
		return;
	}

	if (st0_tag == TAG_Zero)
		return;

	if (st0_tag == TAG_Special)
		st0_tag = FPU_Special(st0_ptr);

	if (st0_tag == TW_Infinity) {
		if (signnegative(st0_ptr))
			arith_invalid(0);	/* sqrt(-Infinity) is invalid */
		return;
	} else if (st0_tag == TW_Denormal) {
		if (signnegative(st0_ptr)) {
			arith_invalid(0);	/* sqrt(negative) is invalid */
			return;
		}

		if (denormal_operand() < 0)
			return;

		FPU_to_exp16(st0_ptr, st0_ptr);

		expon = exponent16(st0_ptr);

		goto denormal_arg;
	}

	single_arg_error(st0_ptr, st0_tag);

}