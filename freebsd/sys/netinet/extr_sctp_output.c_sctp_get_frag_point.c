#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int sctp_frag_point; int /*<<< orphan*/  peer_hmac_id; int /*<<< orphan*/  peer_auth_chunks; } ;
struct sctp_tcb {TYPE_1__ asoc; TYPE_2__* sctp_ep; } ;
struct sctp_association {int smallest_mtu; } ;
struct TYPE_4__ {int sctp_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCTP_DATA ; 
 scalar_t__ SCTP_DATA_CHUNK_OVERHEAD (struct sctp_tcb*) ; 
 int SCTP_MIN_OVERHEAD ; 
 int SCTP_MIN_V4_OVERHEAD ; 
 int SCTP_PCB_FLAGS_BOUND_V6 ; 
 scalar_t__ sctp_auth_is_required_chunk (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sctp_get_auth_chunk_len (int /*<<< orphan*/ ) ; 

int
sctp_get_frag_point(struct sctp_tcb *stcb,
    struct sctp_association *asoc)
{
	int siz, ovh;

	/*
	 * For endpoints that have both v6 and v4 addresses we must reserve
	 * room for the ipv6 header, for those that are only dealing with V4
	 * we use a larger frag point.
	 */
	if (stcb->sctp_ep->sctp_flags & SCTP_PCB_FLAGS_BOUND_V6) {
		ovh = SCTP_MIN_OVERHEAD;
	} else {
		ovh = SCTP_MIN_V4_OVERHEAD;
	}
	ovh += SCTP_DATA_CHUNK_OVERHEAD(stcb);
	if (stcb->asoc.sctp_frag_point > asoc->smallest_mtu)
		siz = asoc->smallest_mtu - ovh;
	else
		siz = (stcb->asoc.sctp_frag_point - ovh);
	/*
	 * if (siz > (MCLBYTES-sizeof(struct sctp_data_chunk))) {
	 */
	/* A data chunk MUST fit in a cluster */
	/* siz = (MCLBYTES - sizeof(struct sctp_data_chunk)); */
	/* } */

	/* adjust for an AUTH chunk if DATA requires auth */
	if (sctp_auth_is_required_chunk(SCTP_DATA, stcb->asoc.peer_auth_chunks))
		siz -= sctp_get_auth_chunk_len(stcb->asoc.peer_hmac_id);

	if (siz % 4) {
		/* make it an even word boundary please */
		siz -= (siz % 4);
	}
	return (siz);
}