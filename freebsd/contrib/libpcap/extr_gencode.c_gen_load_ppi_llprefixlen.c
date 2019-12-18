#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int k; } ;
struct slist {TYPE_1__ s; } ;
struct TYPE_7__ {int reg; } ;
struct TYPE_8__ {TYPE_2__ off_linkhdr; } ;
typedef  TYPE_3__ compiler_state_t ;

/* Variables and functions */
 int BPF_ABS ; 
 int BPF_ALU ; 
 int BPF_B ; 
 int BPF_K ; 
 int BPF_LD ; 
 int BPF_LSH ; 
 int BPF_MISC ; 
 int BPF_OR ; 
 int BPF_ST ; 
 int BPF_TAX ; 
 int BPF_X ; 
 struct slist* new_stmt (TYPE_3__*,int) ; 
 int /*<<< orphan*/  sappend (struct slist*,struct slist*) ; 

__attribute__((used)) static struct slist *
gen_load_ppi_llprefixlen(compiler_state_t *cstate)
{
	struct slist *s1, *s2;

	/*
	 * Generate code to load the length of the radiotap header
	 * into the register assigned to hold that length, if one has
	 * been assigned.
	 */
	if (cstate->off_linkhdr.reg != -1) {
		/*
		 * The 2 bytes at offsets of 2 and 3 from the beginning
		 * of the radiotap header are the length of the radiotap
		 * header; unfortunately, it's little-endian, so we have
		 * to load it a byte at a time and construct the value.
		 */

		/*
		 * Load the high-order byte, at an offset of 3, shift it
		 * left a byte, and put the result in the X register.
		 */
		s1 = new_stmt(cstate, BPF_LD|BPF_B|BPF_ABS);
		s1->s.k = 3;
		s2 = new_stmt(cstate, BPF_ALU|BPF_LSH|BPF_K);
		sappend(s1, s2);
		s2->s.k = 8;
		s2 = new_stmt(cstate, BPF_MISC|BPF_TAX);
		sappend(s1, s2);

		/*
		 * Load the next byte, at an offset of 2, and OR the
		 * value from the X register into it.
		 */
		s2 = new_stmt(cstate, BPF_LD|BPF_B|BPF_ABS);
		sappend(s1, s2);
		s2->s.k = 2;
		s2 = new_stmt(cstate, BPF_ALU|BPF_OR|BPF_X);
		sappend(s1, s2);

		/*
		 * Now allocate a register to hold that value and store
		 * it.
		 */
		s2 = new_stmt(cstate, BPF_ST);
		s2->s.k = cstate->off_linkhdr.reg;
		sappend(s1, s2);

		/*
		 * Now move it into the X register.
		 */
		s2 = new_stmt(cstate, BPF_MISC|BPF_TAX);
		sappend(s1, s2);

		return (s1);
	} else
		return (NULL);
}