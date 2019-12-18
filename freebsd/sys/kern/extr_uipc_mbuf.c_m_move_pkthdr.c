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
struct TYPE_2__ {int csum_flags; int /*<<< orphan*/ * snd_tag; int /*<<< orphan*/  tags; } ;
struct mbuf {int m_flags; TYPE_1__ m_pkthdr; int /*<<< orphan*/  m_pktdat; int /*<<< orphan*/  m_data; } ;

/* Variables and functions */
 int CSUM_SND_TAG ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  M_ASSERTPKTHDR (struct mbuf*) ; 
 int M_COPYFLAGS ; 
 int M_EXT ; 
 int M_NOMAP ; 
 int M_PKTHDR ; 
 int /*<<< orphan*/  SLIST_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m_tag_delete_chain (struct mbuf*,int /*<<< orphan*/ *) ; 

void
m_move_pkthdr(struct mbuf *to, struct mbuf *from)
{

#if 0
	/* see below for why these are not enabled */
	M_ASSERTPKTHDR(to);
	/* Note: with MAC, this may not be a good assertion. */
	KASSERT(SLIST_EMPTY(&to->m_pkthdr.tags),
	    ("m_move_pkthdr: to has tags"));
#endif
#ifdef MAC
	/*
	 * XXXMAC: It could be this should also occur for non-MAC?
	 */
	if (to->m_flags & M_PKTHDR)
		m_tag_delete_chain(to, NULL);
#endif
	to->m_flags = (from->m_flags & M_COPYFLAGS) |
	    (to->m_flags & (M_EXT | M_NOMAP));
	if ((to->m_flags & M_EXT) == 0)
		to->m_data = to->m_pktdat;
	to->m_pkthdr = from->m_pkthdr;		/* especially tags */
	SLIST_INIT(&from->m_pkthdr.tags);	/* purge tags from src */
	from->m_flags &= ~M_PKTHDR;
	if (from->m_pkthdr.csum_flags & CSUM_SND_TAG) {
		from->m_pkthdr.csum_flags &= ~CSUM_SND_TAG;
		from->m_pkthdr.snd_tag = NULL;
	}
}