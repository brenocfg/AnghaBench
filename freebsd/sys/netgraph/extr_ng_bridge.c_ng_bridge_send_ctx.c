#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ng_bridge_send_ctx {int error; int manycast; TYPE_3__* incoming; int /*<<< orphan*/  m; TYPE_3__* foundFirst; } ;
struct TYPE_5__ {scalar_t__ len; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;
typedef  TYPE_3__* link_p ;
typedef  int /*<<< orphan*/  hook_p ;
struct TYPE_6__ {int /*<<< orphan*/  xmitBroadcasts; int /*<<< orphan*/  xmitMulticasts; int /*<<< orphan*/  xmitOctets; int /*<<< orphan*/  xmitPackets; int /*<<< orphan*/  memoryFailures; } ;
struct TYPE_7__ {int /*<<< orphan*/  hook; TYPE_2__ stats; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 TYPE_3__* NG_HOOK_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_SEND_DATA_ONLY (int,int /*<<< orphan*/ ,struct mbuf*) ; 
 struct mbuf* m_dup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ng_bridge_send_ctx(hook_p dst, void *arg)
{
	struct ng_bridge_send_ctx *ctx = arg;
	link_p destLink = NG_HOOK_PRIVATE(dst);
	struct mbuf *m2 = NULL;
	int error = 0;

	/* Skip incoming link */
	if (destLink == ctx->incoming) {
		return (1);
	}

	if (ctx->foundFirst == NULL) {
		/*
		 * This is the first usable link we have found.
		 * Reserve it for the originals.
		 * If we never find another we save a copy.
		 */
		ctx->foundFirst = destLink;
		return (1);
	}

	/*
	 * It's usable link but not the reserved (first) one.
	 * Copy mbuf info for sending.
	 */
	m2 = m_dup(ctx->m, M_NOWAIT);	/* XXX m_copypacket() */
	if (m2 == NULL) {
		ctx->incoming->stats.memoryFailures++;
		ctx->error = ENOBUFS;
		return (0);	       /* abort loop */
	}


	/* Update stats */
	destLink->stats.xmitPackets++;
	destLink->stats.xmitOctets += m2->m_pkthdr.len;
	switch (ctx->manycast) {
	 default:					/* unknown unicast */
		break;
	 case 1:					/* multicast */
		destLink->stats.xmitMulticasts++;
		break;
	 case 2:					/* broadcast */
		destLink->stats.xmitBroadcasts++;
		break;
	}

	/* Send packet */
	NG_SEND_DATA_ONLY(error, destLink->hook, m2);
	if(error)
	  ctx->error = error;
	return (1);
}