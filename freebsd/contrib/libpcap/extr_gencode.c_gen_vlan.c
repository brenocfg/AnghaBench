#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct block {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  constant_part; } ;
struct TYPE_9__ {int /*<<< orphan*/  constant_part; int /*<<< orphan*/  is_variable; } ;
struct TYPE_12__ {scalar_t__ label_stack_depth; int linktype; scalar_t__ vlan_stack_depth; TYPE_3__* bpf_pcap; TYPE_2__ off_outermostlinkhdr; TYPE_1__ off_linkhdr; } ;
typedef  TYPE_4__ compiler_state_t ;
struct TYPE_11__ {int bpf_codegen_flags; } ;

/* Variables and functions */
 int BPF_SPECIAL_VLAN_HANDLING ; 
#define  DLT_EN10MB 134 
#define  DLT_IEEE802_11 133 
#define  DLT_IEEE802_11_RADIO 132 
#define  DLT_IEEE802_11_RADIO_AVS 131 
#define  DLT_NETANALYZER 130 
#define  DLT_NETANALYZER_TRANSPARENT 129 
#define  DLT_PRISM_HEADER 128 
 int /*<<< orphan*/  bpf_error (TYPE_4__*,char*,...) ; 
 struct block* gen_vlan_bpf_extensions (TYPE_4__*,int) ; 
 struct block* gen_vlan_no_bpf_extensions (TYPE_4__*,int) ; 

struct block *
gen_vlan(compiler_state_t *cstate, int vlan_num)
{
	struct	block	*b0;

	/* can't check for VLAN-encapsulated packets inside MPLS */
	if (cstate->label_stack_depth > 0)
		bpf_error(cstate, "no VLAN match after MPLS");

	/*
	 * Check for a VLAN packet, and then change the offsets to point
	 * to the type and data fields within the VLAN packet.  Just
	 * increment the offsets, so that we can support a hierarchy, e.g.
	 * "vlan 300 && vlan 200" to capture VLAN 200 encapsulated within
	 * VLAN 100.
	 *
	 * XXX - this is a bit of a kludge.  If we were to split the
	 * compiler into a parser that parses an expression and
	 * generates an expression tree, and a code generator that
	 * takes an expression tree (which could come from our
	 * parser or from some other parser) and generates BPF code,
	 * we could perhaps make the offsets parameters of routines
	 * and, in the handler for an "AND" node, pass to subnodes
	 * other than the VLAN node the adjusted offsets.
	 *
	 * This would mean that "vlan" would, instead of changing the
	 * behavior of *all* tests after it, change only the behavior
	 * of tests ANDed with it.  That would change the documented
	 * semantics of "vlan", which might break some expressions.
	 * However, it would mean that "(vlan and ip) or ip" would check
	 * both for VLAN-encapsulated IP and IP-over-Ethernet, rather than
	 * checking only for VLAN-encapsulated IP, so that could still
	 * be considered worth doing; it wouldn't break expressions
	 * that are of the form "vlan and ..." or "vlan N and ...",
	 * which I suspect are the most common expressions involving
	 * "vlan".  "vlan or ..." doesn't necessarily do what the user
	 * would really want, now, as all the "or ..." tests would
	 * be done assuming a VLAN, even though the "or" could be viewed
	 * as meaning "or, if this isn't a VLAN packet...".
	 */
	switch (cstate->linktype) {

	case DLT_EN10MB:
	case DLT_NETANALYZER:
	case DLT_NETANALYZER_TRANSPARENT:
#if defined(SKF_AD_VLAN_TAG_PRESENT)
		/* Verify that this is the outer part of the packet and
		 * not encapsulated somehow. */
		if (cstate->vlan_stack_depth == 0 && !cstate->off_linkhdr.is_variable &&
		    cstate->off_linkhdr.constant_part ==
		    cstate->off_outermostlinkhdr.constant_part) {
			/*
			 * Do we need special VLAN handling?
			 */
			if (cstate->bpf_pcap->bpf_codegen_flags & BPF_SPECIAL_VLAN_HANDLING)
				b0 = gen_vlan_bpf_extensions(cstate, vlan_num);
			else
				b0 = gen_vlan_no_bpf_extensions(cstate, vlan_num);
		} else
#endif
			b0 = gen_vlan_no_bpf_extensions(cstate, vlan_num);
                break;

	case DLT_IEEE802_11:
	case DLT_PRISM_HEADER:
	case DLT_IEEE802_11_RADIO_AVS:
	case DLT_IEEE802_11_RADIO:
		b0 = gen_vlan_no_bpf_extensions(cstate, vlan_num);
		break;

	default:
		bpf_error(cstate, "no VLAN support for data link type %d",
		      cstate->linktype);
		/*NOTREACHED*/
	}

        cstate->vlan_stack_depth++;

	return (b0);
}