#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pfsync_state_peer {scalar_t__ state; int /*<<< orphan*/  seqlo; } ;
struct TYPE_2__ {scalar_t__ state; int /*<<< orphan*/  seqlo; } ;
struct pf_state {TYPE_1__ dst; TYPE_1__ src; } ;

/* Variables and functions */
 int /*<<< orphan*/  PF_STATE_LOCK_ASSERT (struct pf_state*) ; 
 scalar_t__ PF_TCPS_PROXY_SRC ; 
 scalar_t__ SEQ_GT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TCPS_SYN_SENT ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pf_state_peer_ntoh (struct pfsync_state_peer*,TYPE_1__*) ; 

__attribute__((used)) static int
pfsync_upd_tcp(struct pf_state *st, struct pfsync_state_peer *src,
    struct pfsync_state_peer *dst)
{
	int sync = 0;

	PF_STATE_LOCK_ASSERT(st);

	/*
	 * The state should never go backwards except
	 * for syn-proxy states.  Neither should the
	 * sequence window slide backwards.
	 */
	if ((st->src.state > src->state &&
	    (st->src.state < PF_TCPS_PROXY_SRC ||
	    src->state >= PF_TCPS_PROXY_SRC)) ||

	    (st->src.state == src->state &&
	    SEQ_GT(st->src.seqlo, ntohl(src->seqlo))))
		sync++;
	else
		pf_state_peer_ntoh(src, &st->src);

	if ((st->dst.state > dst->state) ||

	    (st->dst.state >= TCPS_SYN_SENT &&
	    SEQ_GT(st->dst.seqlo, ntohl(dst->seqlo))))
		sync++;
	else
		pf_state_peer_ntoh(dst, &st->dst);

	return (sync);
}