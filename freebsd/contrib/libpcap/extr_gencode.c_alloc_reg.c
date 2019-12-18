#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int* regused; size_t curreg; } ;
typedef  TYPE_1__ compiler_state_t ;

/* Variables and functions */
 int BPF_MEMWORDS ; 
 int /*<<< orphan*/  bpf_error (TYPE_1__*,char*) ; 

__attribute__((used)) static int
alloc_reg(compiler_state_t *cstate)
{
	int n = BPF_MEMWORDS;

	while (--n >= 0) {
		if (cstate->regused[cstate->curreg])
			cstate->curreg = (cstate->curreg + 1) % BPF_MEMWORDS;
		else {
			cstate->regused[cstate->curreg] = 1;
			return cstate->curreg;
		}
	}
	bpf_error(cstate, "too many registers needed to evaluate expression");
	/* NOTREACHED */
}