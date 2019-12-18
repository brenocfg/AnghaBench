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
 int FPU_normalize (int /*<<< orphan*/ *) ; 
 int FPU_round_to_int (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  FPU_settag0 (int) ; 
 scalar_t__ TAG_Special ; 
 scalar_t__ TAG_Valid ; 
 scalar_t__ TAG_Zero ; 
 scalar_t__ TW_Denormal ; 
 scalar_t__ TW_Infinity ; 
 scalar_t__ denormal_operand () ; 
 int exponent (int /*<<< orphan*/ *) ; 
 scalar_t__ getsign (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_precision_flag (int) ; 
 int /*<<< orphan*/  setexponent16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  setsign (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  single_arg_error (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void frndint_(FPU_REG *st0_ptr, u_char st0_tag)
{
	int flags, tag;

	if (st0_tag == TAG_Valid) {
		u_char sign;

	      denormal_arg:

		sign = getsign(st0_ptr);

		if (exponent(st0_ptr) > 63)
			return;

		if (st0_tag == TW_Denormal) {
			if (denormal_operand() < 0)
				return;
		}

		/* Fortunately, this can't overflow to 2^64 */
		if ((flags = FPU_round_to_int(st0_ptr, st0_tag)))
			set_precision_flag(flags);

		setexponent16(st0_ptr, 63);
		tag = FPU_normalize(st0_ptr);
		setsign(st0_ptr, sign);
		FPU_settag0(tag);
		return;
	}

	if (st0_tag == TAG_Zero)
		return;

	if (st0_tag == TAG_Special)
		st0_tag = FPU_Special(st0_ptr);

	if (st0_tag == TW_Denormal)
		goto denormal_arg;
	else if (st0_tag == TW_Infinity)
		return;
	else
		single_arg_error(st0_ptr, st0_tag);
}