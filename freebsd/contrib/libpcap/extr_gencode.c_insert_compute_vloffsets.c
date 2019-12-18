#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int k; } ;
struct slist {TYPE_3__ s; } ;
struct block {struct slist* stmts; } ;
struct TYPE_17__ {int reg; } ;
struct TYPE_15__ {int reg; } ;
struct TYPE_14__ {int reg; scalar_t__ is_variable; } ;
struct TYPE_18__ {int outermostlinktype; TYPE_4__ off_linktype; TYPE_2__ off_linkpl; scalar_t__ is_vlan_vloffset; TYPE_1__ off_linkhdr; } ;
typedef  TYPE_5__ compiler_state_t ;

/* Variables and functions */
 int BPF_IMM ; 
 int BPF_LD ; 
 int BPF_ST ; 
 int BPF_W ; 
#define  DLT_IEEE802_11 132 
#define  DLT_IEEE802_11_RADIO 131 
#define  DLT_IEEE802_11_RADIO_AVS 130 
#define  DLT_PPI 129 
#define  DLT_PRISM_HEADER 128 
 void* alloc_reg (TYPE_5__*) ; 
 struct slist* gen_load_802_11_header_len (TYPE_5__*,struct slist*,struct slist*) ; 
 struct slist* gen_load_avs_llprefixlen (TYPE_5__*) ; 
 struct slist* gen_load_ppi_llprefixlen (TYPE_5__*) ; 
 struct slist* gen_load_prism_llprefixlen (TYPE_5__*) ; 
 struct slist* gen_load_radiotap_llprefixlen (TYPE_5__*) ; 
 struct slist* new_stmt (TYPE_5__*,int) ; 
 int /*<<< orphan*/  sappend (struct slist*,struct slist*) ; 

__attribute__((used)) static void
insert_compute_vloffsets(compiler_state_t *cstate, struct block *b)
{
	struct slist *s;

	/* There is an implicit dependency between the link
	 * payload and link header since the payload computation
	 * includes the variable part of the header. Therefore,
	 * if nobody else has allocated a register for the link
	 * header and we need it, do it now. */
	if (cstate->off_linkpl.reg != -1 && cstate->off_linkhdr.is_variable &&
	    cstate->off_linkhdr.reg == -1)
		cstate->off_linkhdr.reg = alloc_reg(cstate);

	/*
	 * For link-layer types that have a variable-length header
	 * preceding the link-layer header, generate code to load
	 * the offset of the link-layer header into the register
	 * assigned to that offset, if any.
	 *
	 * XXX - this, and the next switch statement, won't handle
	 * encapsulation of 802.11 or 802.11+radio information in
	 * some other protocol stack.  That's significantly more
	 * complicated.
	 */
	switch (cstate->outermostlinktype) {

	case DLT_PRISM_HEADER:
		s = gen_load_prism_llprefixlen(cstate);
		break;

	case DLT_IEEE802_11_RADIO_AVS:
		s = gen_load_avs_llprefixlen(cstate);
		break;

	case DLT_IEEE802_11_RADIO:
		s = gen_load_radiotap_llprefixlen(cstate);
		break;

	case DLT_PPI:
		s = gen_load_ppi_llprefixlen(cstate);
		break;

	default:
		s = NULL;
		break;
	}

	/*
	 * For link-layer types that have a variable-length link-layer
	 * header, generate code to load the offset of the link-layer
	 * payload into the register assigned to that offset, if any.
	 */
	switch (cstate->outermostlinktype) {

	case DLT_IEEE802_11:
	case DLT_PRISM_HEADER:
	case DLT_IEEE802_11_RADIO_AVS:
	case DLT_IEEE802_11_RADIO:
	case DLT_PPI:
		s = gen_load_802_11_header_len(cstate, s, b->stmts);
		break;
	}

	/*
	 * If there there is no initialization yet and we need variable
	 * length offsets for VLAN, initialize them to zero
	 */
	if (s == NULL && cstate->is_vlan_vloffset) {
		struct slist *s2;

		if (cstate->off_linkpl.reg == -1)
			cstate->off_linkpl.reg = alloc_reg(cstate);
		if (cstate->off_linktype.reg == -1)
			cstate->off_linktype.reg = alloc_reg(cstate);

		s = new_stmt(cstate, BPF_LD|BPF_W|BPF_IMM);
		s->s.k = 0;
		s2 = new_stmt(cstate, BPF_ST);
		s2->s.k = cstate->off_linkpl.reg;
		sappend(s, s2);
		s2 = new_stmt(cstate, BPF_ST);
		s2->s.k = cstate->off_linktype.reg;
		sappend(s, s2);
	}

	/*
	 * If we have any offset-loading code, append all the
	 * existing statements in the block to those statements,
	 * and make the resulting list the list of statements
	 * for the block.
	 */
	if (s != NULL) {
		sappend(s, b->stmts);
		b->stmts = s;
	}
}