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
typedef  int /*<<< orphan*/  u_int ;
struct block {int dummy; } ;
typedef  enum e_offrel { ____Placeholder_e_offrel } e_offrel ;
typedef  int /*<<< orphan*/  compiler_state_t ;
typedef  int /*<<< orphan*/  bpf_int32 ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_JGT ; 
 struct block* gen_ncmp (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct block *
gen_cmp_gt(compiler_state_t *cstate, enum e_offrel offrel, u_int offset,
    u_int size, bpf_int32 v)
{
	return gen_ncmp(cstate, offrel, offset, size, 0xffffffff, BPF_JGT, 0, v);
}