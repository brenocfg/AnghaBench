#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int k; } ;
struct slist {TYPE_1__ s; } ;
struct TYPE_9__ {int constant_part; } ;
struct TYPE_8__ {int off_nl; TYPE_6__ off_linkpl; } ;
typedef  TYPE_2__ compiler_state_t ;

/* Variables and functions */
 int BPF_ADD ; 
 int BPF_ALU ; 
 int BPF_AND ; 
 int BPF_B ; 
 int BPF_IND ; 
 int BPF_K ; 
 int BPF_LD ; 
 int BPF_LDX ; 
 int BPF_LSH ; 
 int BPF_MISC ; 
 int BPF_MSH ; 
 int BPF_TAX ; 
 int BPF_X ; 
 struct slist* gen_abs_offset_varpart (TYPE_2__*,TYPE_6__*) ; 
 struct slist* new_stmt (TYPE_2__*,int) ; 
 int /*<<< orphan*/  sappend (struct slist*,struct slist*) ; 

__attribute__((used)) static struct slist *
gen_loadx_iphdrlen(compiler_state_t *cstate)
{
	struct slist *s, *s2;

	s = gen_abs_offset_varpart(cstate, &cstate->off_linkpl);
	if (s != NULL) {
		/*
		 * The offset of the link-layer payload has a variable
		 * part.  "s" points to a list of statements that put
		 * the variable part of that offset into the X register.
		 *
		 * The 4*([k]&0xf) addressing mode can't be used, as we
		 * don't have a constant offset, so we have to load the
		 * value in question into the A register and add to it
		 * the value from the X register.
		 */
		s2 = new_stmt(cstate, BPF_LD|BPF_IND|BPF_B);
		s2->s.k = cstate->off_linkpl.constant_part + cstate->off_nl;
		sappend(s, s2);
		s2 = new_stmt(cstate, BPF_ALU|BPF_AND|BPF_K);
		s2->s.k = 0xf;
		sappend(s, s2);
		s2 = new_stmt(cstate, BPF_ALU|BPF_LSH|BPF_K);
		s2->s.k = 2;
		sappend(s, s2);

		/*
		 * The A register now contains the length of the IP header.
		 * We need to add to it the variable part of the offset of
		 * the link-layer payload, which is still in the X
		 * register, and move the result into the X register.
		 */
		sappend(s, new_stmt(cstate, BPF_ALU|BPF_ADD|BPF_X));
		sappend(s, new_stmt(cstate, BPF_MISC|BPF_TAX));
	} else {
		/*
		 * The offset of the link-layer payload is a constant,
		 * so no code was generated to load the (non-existent)
		 * variable part of that offset.
		 *
		 * This means we can use the 4*([k]&0xf) addressing
		 * mode.  Load the length of the IPv4 header, which
		 * is at an offset of cstate->off_nl from the beginning of
		 * the link-layer payload, and thus at an offset of
		 * cstate->off_linkpl.constant_part + cstate->off_nl from the beginning
		 * of the raw packet data, using that addressing mode.
		 */
		s = new_stmt(cstate, BPF_LDX|BPF_MSH|BPF_B);
		s->s.k = cstate->off_linkpl.constant_part + cstate->off_nl;
	}
	return s;
}