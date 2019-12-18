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
typedef  int /*<<< orphan*/  u8 ;
struct rv_jit_context {int dummy; } ;
typedef  int s64 ;

/* Variables and functions */
 int /*<<< orphan*/  RV_REG_ZERO ; 
 int __ffs (int) ; 
 int /*<<< orphan*/  emit (int /*<<< orphan*/ ,struct rv_jit_context*) ; 
 scalar_t__ is_32b_int (int) ; 
 int /*<<< orphan*/  rv_addi (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rv_addiw (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rv_lui (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rv_slli (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void emit_imm(u8 rd, s64 val, struct rv_jit_context *ctx)
{
	/* Note that the immediate from the add is sign-extended,
	 * which means that we need to compensate this by adding 2^12,
	 * when the 12th bit is set. A simpler way of doing this, and
	 * getting rid of the check, is to just add 2**11 before the
	 * shift. The "Loading a 32-Bit constant" example from the
	 * "Computer Organization and Design, RISC-V edition" book by
	 * Patterson/Hennessy highlights this fact.
	 *
	 * This also means that we need to process LSB to MSB.
	 */
	s64 upper = (val + (1 << 11)) >> 12, lower = val & 0xfff;
	int shift;

	if (is_32b_int(val)) {
		if (upper)
			emit(rv_lui(rd, upper), ctx);

		if (!upper) {
			emit(rv_addi(rd, RV_REG_ZERO, lower), ctx);
			return;
		}

		emit(rv_addiw(rd, rd, lower), ctx);
		return;
	}

	shift = __ffs(upper);
	upper >>= shift;
	shift += 12;

	emit_imm(rd, upper, ctx);

	emit(rv_slli(rd, rd, shift), ctx);
	if (lower)
		emit(rv_addi(rd, rd, lower), ctx);
}