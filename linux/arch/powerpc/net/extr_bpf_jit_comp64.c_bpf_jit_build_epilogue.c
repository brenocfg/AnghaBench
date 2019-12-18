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
struct codegen_context {int dummy; } ;

/* Variables and functions */
 size_t BPF_REG_0 ; 
 int /*<<< orphan*/  PPC_BLR () ; 
 int /*<<< orphan*/  PPC_MR (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * b2p ; 
 int /*<<< orphan*/  bpf_jit_emit_common_epilogue (int /*<<< orphan*/ *,struct codegen_context*) ; 

__attribute__((used)) static void bpf_jit_build_epilogue(u32 *image, struct codegen_context *ctx)
{
	bpf_jit_emit_common_epilogue(image, ctx);

	/* Move result to r3 */
	PPC_MR(3, b2p[BPF_REG_0]);

	PPC_BLR();
}