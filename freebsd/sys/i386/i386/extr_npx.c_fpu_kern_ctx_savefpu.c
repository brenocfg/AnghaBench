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
typedef  scalar_t__ vm_offset_t ;
typedef  union savefpu {int dummy; } savefpu ;
struct fpu_kern_ctx {int /*<<< orphan*/  hwstate1; } ;

/* Variables and functions */
 int /*<<< orphan*/  XSAVE_AREA_ALIGN ; 
 scalar_t__ roundup2 (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static union savefpu *
fpu_kern_ctx_savefpu(struct fpu_kern_ctx *ctx)
{
	vm_offset_t p;

	p = (vm_offset_t)&ctx->hwstate1;
	p = roundup2(p, XSAVE_AREA_ALIGN);
	return ((union savefpu *)p);
}