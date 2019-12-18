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
struct TYPE_2__ {int csum_flags; int /*<<< orphan*/  tags; int /*<<< orphan*/  snd_tag; } ;
struct mbuf {int m_flags; TYPE_1__ m_pkthdr; int /*<<< orphan*/  m_pktdat; int /*<<< orphan*/  m_data; } ;

/* Variables and functions */
 int CSUM_SND_TAG ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  MBUF_CHECKSLEEP (int) ; 
 int /*<<< orphan*/  M_ASSERTPKTHDR (struct mbuf*) ; 
 int M_COPYFLAGS ; 
 int M_EXT ; 
 int M_NOMAP ; 
 int M_PKTHDR ; 
 int /*<<< orphan*/  SLIST_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m_snd_tag_ref (int /*<<< orphan*/ ) ; 
 int m_tag_copy_chain (struct mbuf*,struct mbuf const*,int) ; 
 int /*<<< orphan*/  m_tag_delete_chain (struct mbuf*,int /*<<< orphan*/ *) ; 

int
m_dup_pkthdr(struct mbuf *to, const struct mbuf *from, int how)
{

#if 0
	/*
	 * The mbuf allocator only initializes the pkthdr
	 * when the mbuf is allocated with m_gethdr(). Many users
	 * (e.g. m_copy*, m_prepend) use m_get() and then
	 * smash the pkthdr as needed causing these
	 * assertions to trip.  For now just disable them.
	 */
	M_ASSERTPKTHDR(to);
	/* Note: with MAC, this may not be a good assertion. */
	KASSERT(SLIST_EMPTY(&to->m_pkthdr.tags), ("m_dup_pkthdr: to has tags"));
#endif
	MBUF_CHECKSLEEP(how);
#ifdef MAC
	if (to->m_flags & M_PKTHDR)
		m_tag_delete_chain(to, NULL);
#endif
	to->m_flags = (from->m_flags & M_COPYFLAGS) |
	    (to->m_flags & (M_EXT | M_NOMAP));
	if ((to->m_flags & M_EXT) == 0)
		to->m_data = to->m_pktdat;
	to->m_pkthdr = from->m_pkthdr;
	if (from->m_pkthdr.csum_flags & CSUM_SND_TAG)
		m_snd_tag_ref(from->m_pkthdr.snd_tag);
	SLIST_INIT(&to->m_pkthdr.tags);
	return (m_tag_copy_chain(to, from, how));
}