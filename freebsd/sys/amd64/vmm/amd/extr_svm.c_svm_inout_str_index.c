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
typedef  int /*<<< orphan*/  uint64_t ;
struct svm_regctx {int /*<<< orphan*/  sctx_rsi; int /*<<< orphan*/  sctx_rdi; } ;

/* Variables and functions */

__attribute__((used)) static uint64_t
svm_inout_str_index(struct svm_regctx *regs, int in)
{
	uint64_t val;

	val = in ? regs->sctx_rdi : regs->sctx_rsi;

	return (val);
}