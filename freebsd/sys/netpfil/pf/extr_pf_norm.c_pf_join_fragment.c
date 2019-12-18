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
struct pf_frent {scalar_t__ fe_len; scalar_t__ fe_hdrlen; struct mbuf* fe_m; } ;
struct pf_fragment {int /*<<< orphan*/  fr_queue; } ;
struct TYPE_2__ {scalar_t__ len; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;

/* Variables and functions */
 struct pf_frent* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 struct pf_frent* TAILQ_NEXT (struct pf_frent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V_pf_frent_z ; 
 int /*<<< orphan*/  fr_next ; 
 int /*<<< orphan*/  m_adj (struct mbuf*,scalar_t__) ; 
 int /*<<< orphan*/  m_cat (struct mbuf*,struct mbuf*) ; 
 int /*<<< orphan*/  pf_remove_fragment (struct pf_fragment*) ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct pf_frent*) ; 

__attribute__((used)) static struct mbuf *
pf_join_fragment(struct pf_fragment *frag)
{
	struct mbuf *m, *m2;
	struct pf_frent	*frent, *next;

	frent = TAILQ_FIRST(&frag->fr_queue);
	next = TAILQ_NEXT(frent, fr_next);

	m = frent->fe_m;
	m_adj(m, (frent->fe_hdrlen + frent->fe_len) - m->m_pkthdr.len);
	uma_zfree(V_pf_frent_z, frent);
	for (frent = next; frent != NULL; frent = next) {
		next = TAILQ_NEXT(frent, fr_next);

		m2 = frent->fe_m;
		/* Strip off ip header. */
		m_adj(m2, frent->fe_hdrlen);
		/* Strip off any trailing bytes. */
		m_adj(m2, frent->fe_len - m2->m_pkthdr.len);

		uma_zfree(V_pf_frent_z, frent);
		m_cat(m, m2);
	}

	/* Remove from fragment queue. */
	pf_remove_fragment(frag);

	return (m);
}