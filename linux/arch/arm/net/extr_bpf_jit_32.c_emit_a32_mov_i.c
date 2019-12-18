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
typedef  int /*<<< orphan*/  u32 ;
struct jit_ctx {int dummy; } ;
typedef  int /*<<< orphan*/  s8 ;

/* Variables and functions */
 size_t TMP_REG_1 ; 
 int /*<<< orphan*/  arm_bpf_put_reg32 (int /*<<< orphan*/  const,int /*<<< orphan*/  const,struct jit_ctx*) ; 
 int /*<<< orphan*/ ** bpf2a32 ; 
 int /*<<< orphan*/  emit_mov_i (int /*<<< orphan*/  const,int /*<<< orphan*/  const,struct jit_ctx*) ; 
 scalar_t__ is_stacked (int /*<<< orphan*/  const) ; 

__attribute__((used)) static inline void emit_a32_mov_i(const s8 dst, const u32 val,
				  struct jit_ctx *ctx)
{
	const s8 *tmp = bpf2a32[TMP_REG_1];

	if (is_stacked(dst)) {
		emit_mov_i(tmp[1], val, ctx);
		arm_bpf_put_reg32(dst, tmp[1], ctx);
	} else {
		emit_mov_i(dst, val, ctx);
	}
}