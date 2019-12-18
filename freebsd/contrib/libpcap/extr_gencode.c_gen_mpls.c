#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct block {int dummy; } ;
struct TYPE_6__ {scalar_t__ label_stack_depth; int linktype; int off_nl_nosnap; int off_nl; } ;
typedef  TYPE_1__ compiler_state_t ;
typedef  int /*<<< orphan*/  bpf_int32 ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_B ; 
 int /*<<< orphan*/  BPF_W ; 
#define  DLT_C_HDLC 132 
#define  DLT_EN10MB 131 
#define  DLT_NETANALYZER 130 
#define  DLT_NETANALYZER_TRANSPARENT 129 
#define  DLT_PPP 128 
 int /*<<< orphan*/  ETHERTYPE_MPLS ; 
 int /*<<< orphan*/  OR_LINKPL ; 
 int /*<<< orphan*/  OR_PREVMPLSHDR ; 
 int /*<<< orphan*/  PPP_MPLS_UCAST ; 
 int /*<<< orphan*/  bpf_error (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  gen_and (struct block*,struct block*) ; 
 struct block* gen_linktype (TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct block* gen_mcmp (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

struct block *
gen_mpls(compiler_state_t *cstate, int label_num)
{
	struct	block	*b0, *b1;

        if (cstate->label_stack_depth > 0) {
            /* just match the bottom-of-stack bit clear */
            b0 = gen_mcmp(cstate, OR_PREVMPLSHDR, 2, BPF_B, 0, 0x01);
        } else {
            /*
             * We're not in an MPLS stack yet, so check the link-layer
             * type against MPLS.
             */
            switch (cstate->linktype) {

            case DLT_C_HDLC: /* fall through */
            case DLT_EN10MB:
            case DLT_NETANALYZER:
            case DLT_NETANALYZER_TRANSPARENT:
                    b0 = gen_linktype(cstate, ETHERTYPE_MPLS);
                    break;

            case DLT_PPP:
                    b0 = gen_linktype(cstate, PPP_MPLS_UCAST);
                    break;

                    /* FIXME add other DLT_s ...
                     * for Frame-Relay/and ATM this may get messy due to SNAP headers
                     * leave it for now */

            default:
                    bpf_error(cstate, "no MPLS support for data link type %d",
                          cstate->linktype);
                    /*NOTREACHED*/
                    break;
            }
        }

	/* If a specific MPLS label is requested, check it */
	if (label_num >= 0) {
		label_num = label_num << 12; /* label is shifted 12 bits on the wire */
		b1 = gen_mcmp(cstate, OR_LINKPL, 0, BPF_W, (bpf_int32)label_num,
		    0xfffff000); /* only compare the first 20 bits */
		gen_and(b0, b1);
		b0 = b1;
	}

        /*
         * Change the offsets to point to the type and data fields within
         * the MPLS packet.  Just increment the offsets, so that we
         * can support a hierarchy, e.g. "mpls 100000 && mpls 1024" to
         * capture packets with an outer label of 100000 and an inner
         * label of 1024.
         *
         * Increment the MPLS stack depth as well; this indicates that
         * we're checking MPLS-encapsulated headers, to make sure higher
         * level code generators don't try to match against IP-related
         * protocols such as Q_ARP, Q_RARP etc.
         *
         * XXX - this is a bit of a kludge.  See comments in gen_vlan().
         */
        cstate->off_nl_nosnap += 4;
        cstate->off_nl += 4;
        cstate->label_stack_depth++;
	return (b0);
}