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
typedef  int u32 ;
struct bpf_prog_aux {int /*<<< orphan*/  verifier_zext; } ;

/* Variables and functions */
 int /*<<< orphan*/  dst_hi ; 
 int /*<<< orphan*/  dst_lo ; 
 int /*<<< orphan*/  emit_ia32_alu_i (int const,int,int /*<<< orphan*/  const,int /*<<< orphan*/ ,int const,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  emit_ia32_mov_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ **) ; 

__attribute__((used)) static inline void emit_ia32_alu_i64(const bool is64, const u8 op,
				     const u8 dst[], const u32 val,
				     bool dstk, u8 **pprog,
				     const struct bpf_prog_aux *aux)
{
	u8 *prog = *pprog;
	u32 hi = 0;

	if (is64 && (val & (1<<31)))
		hi = (u32)~0;

	emit_ia32_alu_i(is64, false, op, dst_lo, val, dstk, &prog);
	if (is64)
		emit_ia32_alu_i(is64, true, op, dst_hi, hi, dstk, &prog);
	else if (!aux->verifier_zext)
		emit_ia32_mov_i(dst_hi, 0, dstk, &prog);

	*pprog = prog;
}