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
typedef  int u32 ;
struct jit_ctx {int dummy; } ;
typedef  int /*<<< orphan*/  s8 ;

/* Variables and functions */
 int /*<<< orphan*/  emit_a32_mov_i64 (int /*<<< orphan*/  const*,int,struct jit_ctx*) ; 

__attribute__((used)) static inline void emit_a32_mov_se_i64(const bool is64, const s8 dst[],
				       const u32 val, struct jit_ctx *ctx) {
	u64 val64 = val;

	if (is64 && (val & (1<<31)))
		val64 |= 0xffffffff00000000ULL;
	emit_a32_mov_i64(dst, val64, ctx);
}