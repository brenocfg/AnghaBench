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
struct pfsync_softc {int /*<<< orphan*/  sc_imo; struct pfsync_bucket* sc_buckets; TYPE_1__* sc_ifp; } ;
struct pfsync_bucket {int b_flags; scalar_t__ b_len; int /*<<< orphan*/  b_snd; int /*<<< orphan*/  b_id; } ;
struct mbuf {int m_flags; struct mbuf* m_nextpkt; } ;
struct TYPE_4__ {int /*<<< orphan*/  pfsyncs_oerrors; int /*<<< orphan*/  pfsyncs_opackets; } ;
struct TYPE_3__ {int /*<<< orphan*/  if_vnet; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURVNET_RESTORE () ; 
 int /*<<< orphan*/  CURVNET_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IP_RAWOUTPUT ; 
 int M_SKIP_FIREWALL ; 
 int PFSYNCF_BUCKET_PUSH ; 
 int /*<<< orphan*/  PFSYNC_BUCKET_LOCK (struct pfsync_bucket*) ; 
 int /*<<< orphan*/  PFSYNC_BUCKET_UNLOCK (struct pfsync_bucket*) ; 
 scalar_t__ PFSYNC_MINPKT ; 
 TYPE_2__ V_pfsyncstats ; 
 int /*<<< orphan*/  _IF_DEQUEUE_ALL (int /*<<< orphan*/ *,struct mbuf*) ; 
 scalar_t__ ip_output (struct mbuf*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pfsync_buckets ; 
 int /*<<< orphan*/  pfsync_sendout (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pfsyncintr(void *arg)
{
	struct pfsync_softc *sc = arg;
	struct pfsync_bucket *b;
	struct mbuf *m, *n;
	int c;

	CURVNET_SET(sc->sc_ifp->if_vnet);

	for (c = 0; c < pfsync_buckets; c++) {
		b = &sc->sc_buckets[c];

		PFSYNC_BUCKET_LOCK(b);
		if ((b->b_flags & PFSYNCF_BUCKET_PUSH) && b->b_len > PFSYNC_MINPKT) {
			pfsync_sendout(0, b->b_id);
			b->b_flags &= ~PFSYNCF_BUCKET_PUSH;
		}
		_IF_DEQUEUE_ALL(&b->b_snd, m);
		PFSYNC_BUCKET_UNLOCK(b);

		for (; m != NULL; m = n) {

			n = m->m_nextpkt;
			m->m_nextpkt = NULL;

			/*
			 * We distinguish between a deferral packet and our
			 * own pfsync packet based on M_SKIP_FIREWALL
			 * flag. This is XXX.
			 */
			if (m->m_flags & M_SKIP_FIREWALL)
				ip_output(m, NULL, NULL, 0, NULL, NULL);
			else if (ip_output(m, NULL, NULL, IP_RAWOUTPUT, &sc->sc_imo,
			    NULL) == 0)
				V_pfsyncstats.pfsyncs_opackets++;
			else
				V_pfsyncstats.pfsyncs_oerrors++;
		}
	}
	CURVNET_RESTORE();
}