#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_12__ ;

/* Type definitions */
struct TYPE_17__ {int k; } ;
struct slist {TYPE_1__ s; } ;
struct block {int dummy; } ;
struct arth {int regno; struct slist* s; struct block* b; } ;
struct TYPE_16__ {int constant_part; } ;
struct TYPE_18__ {int off_nl; TYPE_12__ off_linkpl; TYPE_12__ off_linkhdr; int /*<<< orphan*/  linktype; } ;
typedef  TYPE_2__ compiler_state_t ;

/* Variables and functions */
 int BPF_ADD ; 
 int BPF_ALU ; 
 int BPF_B ; 
 int BPF_H ; 
 int BPF_IND ; 
 int BPF_LD ; 
 int BPF_MISC ; 
 int BPF_ST ; 
 int BPF_TAX ; 
 int BPF_W ; 
 int BPF_X ; 
 int /*<<< orphan*/  DLT_IEEE802_11_RADIO ; 
 int /*<<< orphan*/  DLT_IEEE802_11_RADIO_AVS ; 
 int /*<<< orphan*/  DLT_PRISM_HEADER ; 
 int /*<<< orphan*/  OR_LINKPL ; 
#define  Q_ARP 149 
#define  Q_ATALK 148 
#define  Q_CARP 147 
#define  Q_DECNET 146 
#define  Q_ICMP 145 
#define  Q_ICMPV6 144 
#define  Q_IGMP 143 
#define  Q_IGRP 142 
#define  Q_IP 141 
#define  Q_IPV6 140 
#define  Q_LAT 139 
#define  Q_LINK 138 
#define  Q_MOPDL 137 
#define  Q_MOPRC 136 
#define  Q_PIM 135 
#define  Q_RADIO 134 
#define  Q_RARP 133 
#define  Q_SCA 132 
#define  Q_SCTP 131 
#define  Q_TCP 130 
#define  Q_UDP 129 
#define  Q_VRRP 128 
 int alloc_reg (TYPE_2__*) ; 
 int /*<<< orphan*/  bpf_error (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  free_reg (TYPE_2__*,int) ; 
 struct slist* gen_abs_offset_varpart (TYPE_2__*,TYPE_12__*) ; 
 int /*<<< orphan*/  gen_and (struct block*,struct block*) ; 
 struct block* gen_cmp (TYPE_2__*,int /*<<< orphan*/ ,int,int,int) ; 
 struct block* gen_ipfrag (TYPE_2__*) ; 
 struct slist* gen_loadx_iphdrlen (TYPE_2__*) ; 
 struct block* gen_proto_abbrev (TYPE_2__*,int const) ; 
 struct slist* new_stmt (TYPE_2__*,int) ; 
 int /*<<< orphan*/  sappend (struct slist*,struct slist*) ; 
 struct slist* xfer_to_a (TYPE_2__*,struct arth*) ; 
 struct slist* xfer_to_x (TYPE_2__*,struct arth*) ; 

struct arth *
gen_load(compiler_state_t *cstate, int proto, struct arth *inst, int size)
{
	struct slist *s, *tmp;
	struct block *b;
	int regno = alloc_reg(cstate);

	free_reg(cstate, inst->regno);
	switch (size) {

	default:
		bpf_error(cstate, "data size must be 1, 2, or 4");

	case 1:
		size = BPF_B;
		break;

	case 2:
		size = BPF_H;
		break;

	case 4:
		size = BPF_W;
		break;
	}
	switch (proto) {
	default:
		bpf_error(cstate, "unsupported index operation");

	case Q_RADIO:
		/*
		 * The offset is relative to the beginning of the packet
		 * data, if we have a radio header.  (If we don't, this
		 * is an error.)
		 */
		if (cstate->linktype != DLT_IEEE802_11_RADIO_AVS &&
		    cstate->linktype != DLT_IEEE802_11_RADIO &&
		    cstate->linktype != DLT_PRISM_HEADER)
			bpf_error(cstate, "radio information not present in capture");

		/*
		 * Load into the X register the offset computed into the
		 * register specified by "index".
		 */
		s = xfer_to_x(cstate, inst);

		/*
		 * Load the item at that offset.
		 */
		tmp = new_stmt(cstate, BPF_LD|BPF_IND|size);
		sappend(s, tmp);
		sappend(inst->s, s);
		break;

	case Q_LINK:
		/*
		 * The offset is relative to the beginning of
		 * the link-layer header.
		 *
		 * XXX - what about ATM LANE?  Should the index be
		 * relative to the beginning of the AAL5 frame, so
		 * that 0 refers to the beginning of the LE Control
		 * field, or relative to the beginning of the LAN
		 * frame, so that 0 refers, for Ethernet LANE, to
		 * the beginning of the destination address?
		 */
		s = gen_abs_offset_varpart(cstate, &cstate->off_linkhdr);

		/*
		 * If "s" is non-null, it has code to arrange that the
		 * X register contains the length of the prefix preceding
		 * the link-layer header.  Add to it the offset computed
		 * into the register specified by "index", and move that
		 * into the X register.  Otherwise, just load into the X
		 * register the offset computed into the register specified
		 * by "index".
		 */
		if (s != NULL) {
			sappend(s, xfer_to_a(cstate, inst));
			sappend(s, new_stmt(cstate, BPF_ALU|BPF_ADD|BPF_X));
			sappend(s, new_stmt(cstate, BPF_MISC|BPF_TAX));
		} else
			s = xfer_to_x(cstate, inst);

		/*
		 * Load the item at the sum of the offset we've put in the
		 * X register and the offset of the start of the link
		 * layer header (which is 0 if the radio header is
		 * variable-length; that header length is what we put
		 * into the X register and then added to the index).
		 */
		tmp = new_stmt(cstate, BPF_LD|BPF_IND|size);
		tmp->s.k = cstate->off_linkhdr.constant_part;
		sappend(s, tmp);
		sappend(inst->s, s);
		break;

	case Q_IP:
	case Q_ARP:
	case Q_RARP:
	case Q_ATALK:
	case Q_DECNET:
	case Q_SCA:
	case Q_LAT:
	case Q_MOPRC:
	case Q_MOPDL:
	case Q_IPV6:
		/*
		 * The offset is relative to the beginning of
		 * the network-layer header.
		 * XXX - are there any cases where we want
		 * cstate->off_nl_nosnap?
		 */
		s = gen_abs_offset_varpart(cstate, &cstate->off_linkpl);

		/*
		 * If "s" is non-null, it has code to arrange that the
		 * X register contains the variable part of the offset
		 * of the link-layer payload.  Add to it the offset
		 * computed into the register specified by "index",
		 * and move that into the X register.  Otherwise, just
		 * load into the X register the offset computed into
		 * the register specified by "index".
		 */
		if (s != NULL) {
			sappend(s, xfer_to_a(cstate, inst));
			sappend(s, new_stmt(cstate, BPF_ALU|BPF_ADD|BPF_X));
			sappend(s, new_stmt(cstate, BPF_MISC|BPF_TAX));
		} else
			s = xfer_to_x(cstate, inst);

		/*
		 * Load the item at the sum of the offset we've put in the
		 * X register, the offset of the start of the network
		 * layer header from the beginning of the link-layer
		 * payload, and the constant part of the offset of the
		 * start of the link-layer payload.
		 */
		tmp = new_stmt(cstate, BPF_LD|BPF_IND|size);
		tmp->s.k = cstate->off_linkpl.constant_part + cstate->off_nl;
		sappend(s, tmp);
		sappend(inst->s, s);

		/*
		 * Do the computation only if the packet contains
		 * the protocol in question.
		 */
		b = gen_proto_abbrev(cstate, proto);
		if (inst->b)
			gen_and(inst->b, b);
		inst->b = b;
		break;

	case Q_SCTP:
	case Q_TCP:
	case Q_UDP:
	case Q_ICMP:
	case Q_IGMP:
	case Q_IGRP:
	case Q_PIM:
	case Q_VRRP:
	case Q_CARP:
		/*
		 * The offset is relative to the beginning of
		 * the transport-layer header.
		 *
		 * Load the X register with the length of the IPv4 header
		 * (plus the offset of the link-layer header, if it's
		 * a variable-length header), in bytes.
		 *
		 * XXX - are there any cases where we want
		 * cstate->off_nl_nosnap?
		 * XXX - we should, if we're built with
		 * IPv6 support, generate code to load either
		 * IPv4, IPv6, or both, as appropriate.
		 */
		s = gen_loadx_iphdrlen(cstate);

		/*
		 * The X register now contains the sum of the variable
		 * part of the offset of the link-layer payload and the
		 * length of the network-layer header.
		 *
		 * Load into the A register the offset relative to
		 * the beginning of the transport layer header,
		 * add the X register to that, move that to the
		 * X register, and load with an offset from the
		 * X register equal to the sum of the constant part of
		 * the offset of the link-layer payload and the offset,
		 * relative to the beginning of the link-layer payload,
		 * of the network-layer header.
		 */
		sappend(s, xfer_to_a(cstate, inst));
		sappend(s, new_stmt(cstate, BPF_ALU|BPF_ADD|BPF_X));
		sappend(s, new_stmt(cstate, BPF_MISC|BPF_TAX));
		sappend(s, tmp = new_stmt(cstate, BPF_LD|BPF_IND|size));
		tmp->s.k = cstate->off_linkpl.constant_part + cstate->off_nl;
		sappend(inst->s, s);

		/*
		 * Do the computation only if the packet contains
		 * the protocol in question - which is true only
		 * if this is an IP datagram and is the first or
		 * only fragment of that datagram.
		 */
		gen_and(gen_proto_abbrev(cstate, proto), b = gen_ipfrag(cstate));
		if (inst->b)
			gen_and(inst->b, b);
		gen_and(gen_proto_abbrev(cstate, Q_IP), b);
		inst->b = b;
		break;
	case Q_ICMPV6:
        /*
        * Do the computation only if the packet contains
        * the protocol in question.
        */
        b = gen_proto_abbrev(cstate, Q_IPV6);
        if (inst->b) {
            gen_and(inst->b, b);
        }
        inst->b = b;

        /*
        * Check if we have an icmp6 next header
        */
        b = gen_cmp(cstate, OR_LINKPL, 6, BPF_B, 58);
        if (inst->b) {
            gen_and(inst->b, b);
        }
        inst->b = b;


        s = gen_abs_offset_varpart(cstate, &cstate->off_linkpl);
        /*
        * If "s" is non-null, it has code to arrange that the
        * X register contains the variable part of the offset
        * of the link-layer payload.  Add to it the offset
        * computed into the register specified by "index",
        * and move that into the X register.  Otherwise, just
        * load into the X register the offset computed into
        * the register specified by "index".
        */
        if (s != NULL) {
            sappend(s, xfer_to_a(cstate, inst));
            sappend(s, new_stmt(cstate, BPF_ALU|BPF_ADD|BPF_X));
            sappend(s, new_stmt(cstate, BPF_MISC|BPF_TAX));
        } else {
            s = xfer_to_x(cstate, inst);
        }

        /*
        * Load the item at the sum of the offset we've put in the
        * X register, the offset of the start of the network
        * layer header from the beginning of the link-layer
        * payload, and the constant part of the offset of the
        * start of the link-layer payload.
        */
        tmp = new_stmt(cstate, BPF_LD|BPF_IND|size);
        tmp->s.k = cstate->off_linkpl.constant_part + cstate->off_nl + 40;

        sappend(s, tmp);
        sappend(inst->s, s);

        break;
	}
	inst->regno = regno;
	s = new_stmt(cstate, BPF_ST);
	s->s.k = regno;
	sappend(inst->s, s);

	return inst;
}