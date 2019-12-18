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
struct jit_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_ADC_R (int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  ARM_ADDS_R (int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  ARM_ADD_R (int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  emit (int /*<<< orphan*/ ,struct jit_ctx*) ; 

__attribute__((used)) static inline void emit_a32_add_r(const u8 dst, const u8 src,
			      const bool is64, const bool hi,
			      struct jit_ctx *ctx) {
	/* 64 bit :
	 *	adds dst_lo, dst_lo, src_lo
	 *	adc dst_hi, dst_hi, src_hi
	 * 32 bit :
	 *	add dst_lo, dst_lo, src_lo
	 */
	if (!hi && is64)
		emit(ARM_ADDS_R(dst, dst, src), ctx);
	else if (hi && is64)
		emit(ARM_ADC_R(dst, dst, src), ctx);
	else
		emit(ARM_ADD_R(dst, dst, src), ctx);
}