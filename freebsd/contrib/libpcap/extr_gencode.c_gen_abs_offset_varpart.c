#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int k; } ;
struct slist {TYPE_1__ s; } ;
typedef  int /*<<< orphan*/  compiler_state_t ;
struct TYPE_5__ {int reg; scalar_t__ is_variable; } ;
typedef  TYPE_2__ bpf_abs_offset ;

/* Variables and functions */
 int BPF_LDX ; 
 int BPF_MEM ; 
 int alloc_reg (int /*<<< orphan*/ *) ; 
 struct slist* new_stmt (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static struct slist *
gen_abs_offset_varpart(compiler_state_t *cstate, bpf_abs_offset *off)
{
	struct slist *s;

	if (off->is_variable) {
		if (off->reg == -1) {
			/*
			 * We haven't yet assigned a register for the
			 * variable part of the offset of the link-layer
			 * header; allocate one.
			 */
			off->reg = alloc_reg(cstate);
		}

		/*
		 * Load the register containing the variable part of the
		 * offset of the link-layer header into the X register.
		 */
		s = new_stmt(cstate, BPF_LDX|BPF_MEM);
		s->s.k = off->reg;
		return s;
	} else {
		/*
		 * That offset isn't variable, there's no variable part,
		 * so we don't need to generate any code.
		 */
		return NULL;
	}
}