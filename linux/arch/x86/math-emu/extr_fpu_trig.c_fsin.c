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
 scalar_t__ FPU_round (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  FPU_settag0 (scalar_t__) ; 
 int /*<<< orphan*/  FPU_to_exp16 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FULL_PRECISION ; 
 scalar_t__ TAG_Special ; 
 scalar_t__ TAG_Valid ; 
 scalar_t__ TAG_Zero ; 
 scalar_t__ TW_Denormal ; 
 scalar_t__ TW_Infinity ; 
 int /*<<< orphan*/  arith_invalid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  changesign (int /*<<< orphan*/ *) ; 
 scalar_t__ denormal_operand () ; 
 int exponent (int /*<<< orphan*/ *) ; 
 scalar_t__ getsign (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poly_sine (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_precision_flag_up () ; 
 int /*<<< orphan*/  setcc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setsign (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  single_arg_error (int /*<<< orphan*/ *,scalar_t__) ; 
 int trig_arg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fsin(FPU_REG *st0_ptr, u_char tag)
{
	u_char arg_sign = getsign(st0_ptr);

	if (tag == TAG_Valid) {
		int q;

		if (exponent(st0_ptr) > -40) {
			if ((q = trig_arg(st0_ptr, 0)) == -1) {
				/* Operand is out of range */
				return 1;
			}

			poly_sine(st0_ptr);

			if (q & 2)
				changesign(st0_ptr);

			setsign(st0_ptr, getsign(st0_ptr) ^ arg_sign);

			/* We do not really know if up or down */
			set_precision_flag_up();
			return 0;
		} else {
			/* For a small arg, the result == the argument */
			set_precision_flag_up();	/* Must be up. */
			return 0;
		}
	}

	if (tag == TAG_Zero) {
		setcc(0);
		return 0;
	}

	if (tag == TAG_Special)
		tag = FPU_Special(st0_ptr);

	if (tag == TW_Denormal) {
		if (denormal_operand() < 0)
			return 1;

		/* For a small arg, the result == the argument */
		/* Underflow may happen */
		FPU_to_exp16(st0_ptr, st0_ptr);

		tag = FPU_round(st0_ptr, 1, 0, FULL_PRECISION, arg_sign);

		FPU_settag0(tag);

		return 0;
	} else if (tag == TW_Infinity) {
		/* The 80486 treats infinity as an invalid operand */
		arith_invalid(0);
		return 1;
	} else {
		single_arg_error(st0_ptr, tag);
		return 1;
	}
}