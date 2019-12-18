#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int k; struct slist* jf; struct slist* jt; } ;
struct slist {TYPE_4__ s; } ;
struct TYPE_12__ {int constant_part; int reg; int is_variable; } ;
struct TYPE_11__ {int reg; int is_variable; scalar_t__ constant_part; } ;
struct TYPE_10__ {int reg; } ;
struct TYPE_14__ {int off_nl; int no_optimize; TYPE_3__ off_linkpl; TYPE_2__ off_linktype; TYPE_1__ off_linkhdr; } ;
typedef  TYPE_5__ compiler_state_t ;

/* Variables and functions */
 int BPF_ADD ; 
 int BPF_ALU ; 
 int BPF_AND ; 
 int BPF_B ; 
 int BPF_H ; 
 int BPF_IND ; 
 int /*<<< orphan*/  BPF_JEQ ; 
 int BPF_K ; 
 int BPF_LD ; 
 int BPF_LDX ; 
 int BPF_MEM ; 
 int BPF_MISC ; 
 int BPF_MUL ; 
 int BPF_ST ; 
 int BPF_STX ; 
 int BPF_TAX ; 
 int BPF_TXA ; 
 int BPF_X ; 
 int /*<<< orphan*/  DLT_EN10MB ; 
 int ETHERTYPE_TEB ; 
 int JMP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PUSH_LINKHDR (TYPE_5__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,void*) ; 
 void* alloc_reg (TYPE_5__*) ; 
 struct slist* new_stmt (TYPE_5__*,int) ; 
 int /*<<< orphan*/  sappend (struct slist*,struct slist*) ; 

__attribute__((used)) static struct slist *
gen_geneve_offsets(compiler_state_t *cstate)
{
	struct slist *s, *s1, *s_proto;

	/* First we need to calculate the offset of the Geneve header
	 * itself. This is composed of the IP header previously calculated
	 * (include any variable link prefix) and stored in A plus the
	 * fixed sized headers (fixed link prefix, MAC length, and UDP
	 * header). */
	s = new_stmt(cstate, BPF_ALU|BPF_ADD|BPF_K);
	s->s.k = cstate->off_linkpl.constant_part + cstate->off_nl + 8;

	/* Stash this in X since we'll need it later. */
	s1 = new_stmt(cstate, BPF_MISC|BPF_TAX);
	sappend(s, s1);

	/* The EtherType in Geneve is 2 bytes in. Calculate this and
	 * store it. */
	s1 = new_stmt(cstate, BPF_ALU|BPF_ADD|BPF_K);
	s1->s.k = 2;
	sappend(s, s1);

	cstate->off_linktype.reg = alloc_reg(cstate);
	cstate->off_linktype.is_variable = 1;
	cstate->off_linktype.constant_part = 0;

	s1 = new_stmt(cstate, BPF_ST);
	s1->s.k = cstate->off_linktype.reg;
	sappend(s, s1);

	/* Load the Geneve option length and mask and shift to get the
	 * number of bytes. It is stored in the first byte of the Geneve
	 * header. */
	s1 = new_stmt(cstate, BPF_LD|BPF_IND|BPF_B);
	s1->s.k = 0;
	sappend(s, s1);

	s1 = new_stmt(cstate, BPF_ALU|BPF_AND|BPF_K);
	s1->s.k = 0x3f;
	sappend(s, s1);

	s1 = new_stmt(cstate, BPF_ALU|BPF_MUL|BPF_K);
	s1->s.k = 4;
	sappend(s, s1);

	/* Add in the rest of the Geneve base header. */
	s1 = new_stmt(cstate, BPF_ALU|BPF_ADD|BPF_K);
	s1->s.k = 8;
	sappend(s, s1);

	/* Add the Geneve header length to its offset and store. */
	s1 = new_stmt(cstate, BPF_ALU|BPF_ADD|BPF_X);
	s1->s.k = 0;
	sappend(s, s1);

	/* Set the encapsulated type as Ethernet. Even though we may
	 * not actually have Ethernet inside there are two reasons this
	 * is useful:
	 * - The linktype field is always in EtherType format regardless
	 *   of whether it is in Geneve or an inner Ethernet frame.
	 * - The only link layer that we have specific support for is
	 *   Ethernet. We will confirm that the packet actually is
	 *   Ethernet at runtime before executing these checks. */
	PUSH_LINKHDR(cstate, DLT_EN10MB, 1, 0, alloc_reg(cstate));

	s1 = new_stmt(cstate, BPF_ST);
	s1->s.k = cstate->off_linkhdr.reg;
	sappend(s, s1);

	/* Calculate whether we have an Ethernet header or just raw IP/
	 * MPLS/etc. If we have Ethernet, advance the end of the MAC offset
	 * and linktype by 14 bytes so that the network header can be found
	 * seamlessly. Otherwise, keep what we've calculated already. */

	/* We have a bare jmp so we can't use the optimizer. */
	cstate->no_optimize = 1;

	/* Load the EtherType in the Geneve header, 2 bytes in. */
	s1 = new_stmt(cstate, BPF_LD|BPF_IND|BPF_H);
	s1->s.k = 2;
	sappend(s, s1);

	/* Load X with the end of the Geneve header. */
	s1 = new_stmt(cstate, BPF_LDX|BPF_MEM);
	s1->s.k = cstate->off_linkhdr.reg;
	sappend(s, s1);

	/* Check if the EtherType is Transparent Ethernet Bridging. At the
	 * end of this check, we should have the total length in X. In
	 * the non-Ethernet case, it's already there. */
	s_proto = new_stmt(cstate, JMP(BPF_JEQ));
	s_proto->s.k = ETHERTYPE_TEB;
	sappend(s, s_proto);

	s1 = new_stmt(cstate, BPF_MISC|BPF_TXA);
	sappend(s, s1);
	s_proto->s.jt = s1;

	/* Since this is Ethernet, use the EtherType of the payload
	 * directly as the linktype. Overwrite what we already have. */
	s1 = new_stmt(cstate, BPF_ALU|BPF_ADD|BPF_K);
	s1->s.k = 12;
	sappend(s, s1);

	s1 = new_stmt(cstate, BPF_ST);
	s1->s.k = cstate->off_linktype.reg;
	sappend(s, s1);

	/* Advance two bytes further to get the end of the Ethernet
	 * header. */
	s1 = new_stmt(cstate, BPF_ALU|BPF_ADD|BPF_K);
	s1->s.k = 2;
	sappend(s, s1);

	/* Move the result to X. */
	s1 = new_stmt(cstate, BPF_MISC|BPF_TAX);
	sappend(s, s1);

	/* Store the final result of our linkpl calculation. */
	cstate->off_linkpl.reg = alloc_reg(cstate);
	cstate->off_linkpl.is_variable = 1;
	cstate->off_linkpl.constant_part = 0;

	s1 = new_stmt(cstate, BPF_STX);
	s1->s.k = cstate->off_linkpl.reg;
	sappend(s, s1);
	s_proto->s.jf = s1;

	cstate->off_nl = 0;

	return s;
}