#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct block {int dummy; } ;
struct TYPE_9__ {scalar_t__ constant_part; } ;
struct TYPE_8__ {scalar_t__ constant_part; int /*<<< orphan*/  reg; int /*<<< orphan*/  is_variable; } ;
struct TYPE_10__ {scalar_t__ off_nl_nosnap; scalar_t__ off_nl; TYPE_2__ off_linkhdr; TYPE_1__ off_linkpl; TYPE_2__ off_linktype; } ;
typedef  TYPE_3__ compiler_state_t ;
typedef  int /*<<< orphan*/  bpf_int32 ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_W ; 
 int /*<<< orphan*/  DLT_PPP ; 
 scalar_t__ ETHERTYPE_PPPOES ; 
 int /*<<< orphan*/  OR_LINKPL ; 
 int /*<<< orphan*/  PUSH_LINKHDR (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_and (struct block*,struct block*) ; 
 struct block* gen_linktype (TYPE_3__*,int /*<<< orphan*/ ) ; 
 struct block* gen_mcmp (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

struct block *
gen_pppoes(compiler_state_t *cstate, int sess_num)
{
	struct block *b0, *b1;

	/*
	 * Test against the PPPoE session link-layer type.
	 */
	b0 = gen_linktype(cstate, (bpf_int32)ETHERTYPE_PPPOES);

	/* If a specific session is requested, check PPPoE session id */
	if (sess_num >= 0) {
		b1 = gen_mcmp(cstate, OR_LINKPL, 0, BPF_W,
		    (bpf_int32)sess_num, 0x0000ffff);
		gen_and(b0, b1);
		b0 = b1;
	}

	/*
	 * Change the offsets to point to the type and data fields within
	 * the PPP packet, and note that this is PPPoE rather than
	 * raw PPP.
	 *
	 * XXX - this is a bit of a kludge.  If we were to split the
	 * compiler into a parser that parses an expression and
	 * generates an expression tree, and a code generator that
	 * takes an expression tree (which could come from our
	 * parser or from some other parser) and generates BPF code,
	 * we could perhaps make the offsets parameters of routines
	 * and, in the handler for an "AND" node, pass to subnodes
	 * other than the PPPoE node the adjusted offsets.
	 *
	 * This would mean that "pppoes" would, instead of changing the
	 * behavior of *all* tests after it, change only the behavior
	 * of tests ANDed with it.  That would change the documented
	 * semantics of "pppoes", which might break some expressions.
	 * However, it would mean that "(pppoes and ip) or ip" would check
	 * both for VLAN-encapsulated IP and IP-over-Ethernet, rather than
	 * checking only for VLAN-encapsulated IP, so that could still
	 * be considered worth doing; it wouldn't break expressions
	 * that are of the form "pppoes and ..." which I suspect are the
	 * most common expressions involving "pppoes".  "pppoes or ..."
	 * doesn't necessarily do what the user would really want, now,
	 * as all the "or ..." tests would be done assuming PPPoE, even
	 * though the "or" could be viewed as meaning "or, if this isn't
	 * a PPPoE packet...".
	 *
	 * The "network-layer" protocol is PPPoE, which has a 6-byte
	 * PPPoE header, followed by a PPP packet.
	 *
	 * There is no HDLC encapsulation for the PPP packet (it's
	 * encapsulated in PPPoES instead), so the link-layer type
	 * starts at the first byte of the PPP packet.  For PPPoE,
	 * that offset is relative to the beginning of the total
	 * link-layer payload, including any 802.2 LLC header, so
	 * it's 6 bytes past cstate->off_nl.
	 */
	PUSH_LINKHDR(cstate, DLT_PPP, cstate->off_linkpl.is_variable,
	    cstate->off_linkpl.constant_part + cstate->off_nl + 6, /* 6 bytes past the PPPoE header */
	    cstate->off_linkpl.reg);

	cstate->off_linktype = cstate->off_linkhdr;
	cstate->off_linkpl.constant_part = cstate->off_linkhdr.constant_part + 2;

	cstate->off_nl = 0;
	cstate->off_nl_nosnap = 0;	/* no 802.2 LLC */

	return b0;
}