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
struct TYPE_7__ {int k; } ;
struct slist {TYPE_2__ s; } ;
struct TYPE_6__ {int reg; } ;
struct TYPE_8__ {TYPE_1__ off_linkhdr; } ;
typedef  TYPE_3__ compiler_state_t ;

/* Variables and functions */
 int BPF_ABS ; 
 int BPF_LD ; 
 int BPF_MISC ; 
 int BPF_ST ; 
 int BPF_TAX ; 
 int BPF_W ; 
 struct slist* new_stmt (TYPE_3__*,int) ; 
 int /*<<< orphan*/  sappend (struct slist*,struct slist*) ; 

__attribute__((used)) static struct slist *
gen_load_avs_llprefixlen(compiler_state_t *cstate)
{
	struct slist *s1, *s2;

	/*
	 * Generate code to load the length of the AVS header into
	 * the register assigned to hold that length, if one has been
	 * assigned.  (If one hasn't been assigned, no code we've
	 * generated uses that prefix, so we don't need to generate any
	 * code to load it.)
	 */
	if (cstate->off_linkhdr.reg != -1) {
		/*
		 * The 4 bytes at an offset of 4 from the beginning of
		 * the AVS header are the length of the AVS header.
		 * That field is big-endian.
		 */
		s1 = new_stmt(cstate, BPF_LD|BPF_W|BPF_ABS);
		s1->s.k = 4;

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