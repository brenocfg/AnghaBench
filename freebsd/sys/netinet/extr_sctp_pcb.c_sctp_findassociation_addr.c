#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct sockaddr {int dummy; } ;
struct sctphdr {int /*<<< orphan*/  dest_port; int /*<<< orphan*/  src_port; scalar_t__ v_tag; } ;
struct sctp_tcb {int dummy; } ;
struct sctp_nets {int dummy; } ;
struct sctp_inpcb {int sctp_flags; } ;
struct sctp_chunkhdr {scalar_t__ chunk_type; } ;
struct mbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCTPDBG (int /*<<< orphan*/ ,char*,void*,...) ; 
 int /*<<< orphan*/  SCTP_DEBUG_PCB1 ; 
 scalar_t__ SCTP_INITIATION ; 
 scalar_t__ SCTP_INITIATION_ACK ; 
 int SCTP_PCB_FLAGS_IN_TCPPOOL ; 
 int /*<<< orphan*/  ntohl (scalar_t__) ; 
 struct sctp_tcb* sctp_findassoc_by_vtag (struct sockaddr*,struct sockaddr*,int /*<<< orphan*/ ,struct sctp_inpcb**,struct sctp_nets**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sctp_tcb* sctp_findassociation_addr_sa (struct sockaddr*,struct sockaddr*,struct sctp_inpcb**,struct sctp_nets**,int,int /*<<< orphan*/ ) ; 
 struct sctp_tcb* sctp_findassociation_special_addr (struct mbuf*,int,struct sctphdr*,struct sctp_inpcb**,struct sctp_nets**,struct sockaddr*) ; 

struct sctp_tcb *
sctp_findassociation_addr(struct mbuf *m, int offset,
    struct sockaddr *src, struct sockaddr *dst,
    struct sctphdr *sh, struct sctp_chunkhdr *ch,
    struct sctp_inpcb **inp_p, struct sctp_nets **netp, uint32_t vrf_id)
{
	struct sctp_tcb *stcb;
	struct sctp_inpcb *inp;

	if (sh->v_tag) {
		/* we only go down this path if vtag is non-zero */
		stcb = sctp_findassoc_by_vtag(src, dst, ntohl(sh->v_tag),
		    inp_p, netp, sh->src_port, sh->dest_port, 0, vrf_id, 0);
		if (stcb) {
			return (stcb);
		}
	}

	if (inp_p) {
		stcb = sctp_findassociation_addr_sa(src, dst, inp_p, netp,
		    1, vrf_id);
		inp = *inp_p;
	} else {
		stcb = sctp_findassociation_addr_sa(src, dst, &inp, netp,
		    1, vrf_id);
	}
	SCTPDBG(SCTP_DEBUG_PCB1, "stcb:%p inp:%p\n", (void *)stcb, (void *)inp);
	if (stcb == NULL && inp) {
		/* Found a EP but not this address */
		if ((ch->chunk_type == SCTP_INITIATION) ||
		    (ch->chunk_type == SCTP_INITIATION_ACK)) {
			/*-
			 * special hook, we do NOT return linp or an
			 * association that is linked to an existing
			 * association that is under the TCP pool (i.e. no
			 * listener exists). The endpoint finding routine
			 * will always find a listener before examining the
			 * TCP pool.
			 */
			if (inp->sctp_flags & SCTP_PCB_FLAGS_IN_TCPPOOL) {
				if (inp_p) {
					*inp_p = NULL;
				}
				return (NULL);
			}
			stcb = sctp_findassociation_special_addr(m,
			    offset, sh, &inp, netp, dst);
			if (inp_p != NULL) {
				*inp_p = inp;
			}
		}
	}
	SCTPDBG(SCTP_DEBUG_PCB1, "stcb is %p\n", (void *)stcb);
	return (stcb);
}