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
typedef  int u64 ;
struct jit_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  A64_MOVK (int,int const,int,int) ; 
 int /*<<< orphan*/  A64_MOVN (int,int const,int,int) ; 
 int /*<<< orphan*/  emit (int /*<<< orphan*/ ,struct jit_ctx*) ; 

__attribute__((used)) static inline void emit_addr_mov_i64(const int reg, const u64 val,
				     struct jit_ctx *ctx)
{
	u64 tmp = val;
	int shift = 0;

	emit(A64_MOVN(1, reg, ~tmp & 0xffff, shift), ctx);
	while (shift < 32) {
		tmp >>= 16;
		shift += 16;
		emit(A64_MOVK(1, reg, tmp & 0xffff, shift), ctx);
	}
}