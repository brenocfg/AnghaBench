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
typedef  int uint64_t ;
struct svm_regctx {int sctx_rcx; } ;

/* Variables and functions */

__attribute__((used)) static uint64_t
svm_inout_str_count(struct svm_regctx *regs, int rep)
{
	uint64_t val;

	val = rep ? regs->sctx_rcx : 1;

	return (val);
}