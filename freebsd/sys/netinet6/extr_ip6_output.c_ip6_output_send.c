#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_in6 {int dummy; } ;
struct route_in6 {int dummy; } ;
struct route {int dummy; } ;
struct TYPE_7__ {int csum_flags; int /*<<< orphan*/  snd_tag; int /*<<< orphan*/ * rcvif; } ;
struct mbuf {TYPE_3__ m_pkthdr; TYPE_4__* m_next; } ;
struct m_snd_tag {struct ifnet* ifp; } ;
struct ktls_session {struct m_snd_tag* snd_tag; } ;
struct inpcb {int inp_flags2; struct m_snd_tag* inp_snd_tag; } ;
struct ifnet {int dummy; } ;
struct TYPE_6__ {TYPE_1__* ext_pgs; } ;
struct TYPE_8__ {TYPE_2__ m_ext; } ;
struct TYPE_5__ {int /*<<< orphan*/  tls; } ;

/* Variables and functions */
 int CSUM_SND_TAG ; 
 int EAGAIN ; 
 int INP_RATE_LIMIT_CHANGED ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  in_pcboutput_eagain (struct inpcb*) ; 
 int /*<<< orphan*/  in_pcboutput_txrtlmt (struct inpcb*,struct ifnet*,struct mbuf*) ; 
 int /*<<< orphan*/  ktls_free (struct ktls_session*) ; 
 struct ktls_session* ktls_hold (int /*<<< orphan*/ ) ; 
 int ktls_output_eagain (struct inpcb*,struct ktls_session*) ; 
 int /*<<< orphan*/  m_snd_tag_ref (struct m_snd_tag*) ; 
 scalar_t__ mbuf_has_tls_session (TYPE_4__*) ; 
 int nd6_output_ifp (struct ifnet*,struct ifnet*,struct mbuf*,struct sockaddr_in6*,struct route*) ; 

__attribute__((used)) static int
ip6_output_send(struct inpcb *inp, struct ifnet *ifp, struct ifnet *origifp,
    struct mbuf *m, struct sockaddr_in6 *dst, struct route_in6 *ro)
{
#ifdef KERN_TLS
	struct ktls_session *tls = NULL;
#endif
	struct m_snd_tag *mst;
	int error;

	MPASS((m->m_pkthdr.csum_flags & CSUM_SND_TAG) == 0);
	mst = NULL;

#ifdef KERN_TLS
	/*
	 * If this is an unencrypted TLS record, save a reference to
	 * the record.  This local reference is used to call
	 * ktls_output_eagain after the mbuf has been freed (thus
	 * dropping the mbuf's reference) in if_output.
	 */
	if (m->m_next != NULL && mbuf_has_tls_session(m->m_next)) {
		tls = ktls_hold(m->m_next->m_ext.ext_pgs->tls);
		mst = tls->snd_tag;

		/*
		 * If a TLS session doesn't have a valid tag, it must
		 * have had an earlier ifp mismatch, so drop this
		 * packet.
		 */
		if (mst == NULL) {
			error = EAGAIN;
			goto done;
		}
	}
#endif
#ifdef RATELIMIT
	if (inp != NULL && mst == NULL) {
		if ((inp->inp_flags2 & INP_RATE_LIMIT_CHANGED) != 0 ||
		    (inp->inp_snd_tag != NULL &&
		    inp->inp_snd_tag->ifp != ifp))
			in_pcboutput_txrtlmt(inp, ifp, m);

		if (inp->inp_snd_tag != NULL)
			mst = inp->inp_snd_tag;
	}
#endif
	if (mst != NULL) {
		KASSERT(m->m_pkthdr.rcvif == NULL,
		    ("trying to add a send tag to a forwarded packet"));
		if (mst->ifp != ifp) {
			error = EAGAIN;
			goto done;
		}

		/* stamp send tag on mbuf */
		m->m_pkthdr.snd_tag = m_snd_tag_ref(mst);
		m->m_pkthdr.csum_flags |= CSUM_SND_TAG;
	}

	error = nd6_output_ifp(ifp, origifp, m, dst, (struct route *)ro);

done:
	/* Check for route change invalidating send tags. */
#ifdef KERN_TLS
	if (tls != NULL) {
		if (error == EAGAIN)
			error = ktls_output_eagain(inp, tls);
		ktls_free(tls);
	}
#endif
#ifdef RATELIMIT
	if (error == EAGAIN)
		in_pcboutput_eagain(inp);
#endif
	return (error);
}