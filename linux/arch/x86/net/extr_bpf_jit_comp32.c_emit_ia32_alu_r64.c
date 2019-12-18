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
struct bpf_prog_aux {int /*<<< orphan*/  verifier_zext; } ;

/* Variables and functions */
 int /*<<< orphan*/  dst_hi ; 
 int /*<<< orphan*/  dst_lo ; 
 int /*<<< orphan*/  emit_ia32_alu_r (int const,int,int /*<<< orphan*/  const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  emit_ia32_mov_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  src_hi ; 
 int /*<<< orphan*/  src_lo ; 

__attribute__((used)) static inline void emit_ia32_alu_r64(const bool is64, const u8 op,
				     const u8 dst[], const u8 src[],
				     bool dstk,  bool sstk,
				     u8 **pprog, const struct bpf_prog_aux *aux)
{
	u8 *prog = *pprog;

	emit_ia32_alu_r(is64, false, op, dst_lo, src_lo, dstk, sstk, &prog);
	if (is64)
		emit_ia32_alu_r(is64, true, op, dst_hi, src_hi, dstk, sstk,
				&prog);
	else if (!aux->verifier_zext)
		emit_ia32_mov_i(dst_hi, 0, dstk, &prog);
	*pprog = prog;
}