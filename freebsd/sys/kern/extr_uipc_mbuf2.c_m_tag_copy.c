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
struct m_tag {scalar_t__ m_tag_id; int /*<<< orphan*/  m_tag_len; int /*<<< orphan*/  m_tag_cookie; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (struct m_tag*,char*) ; 
 int /*<<< orphan*/  MBUF_CHECKSLEEP (int) ; 
 scalar_t__ PACKET_TAG_MACLABEL ; 
 int /*<<< orphan*/  bcopy (struct m_tag*,struct m_tag*,int /*<<< orphan*/ ) ; 
 struct m_tag* m_tag_alloc (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  m_tag_free (struct m_tag*) ; 
 int /*<<< orphan*/  mac_mbuf_tag_copy (struct m_tag*,struct m_tag*) ; 
 scalar_t__ mac_mbuf_tag_init (struct m_tag*,int) ; 

struct m_tag *
m_tag_copy(struct m_tag *t, int how)
{
	struct m_tag *p;

	MBUF_CHECKSLEEP(how);
	KASSERT(t, ("m_tag_copy: null tag"));
	p = m_tag_alloc(t->m_tag_cookie, t->m_tag_id, t->m_tag_len, how);
	if (p == NULL)
		return (NULL);
#ifdef MAC
	/*
	 * XXXMAC: we should probably pass off the initialization, and
	 * copying here?  can we hide that PACKET_TAG_MACLABEL is
	 * special from the mbuf code?
	 */
	if (t->m_tag_id == PACKET_TAG_MACLABEL) {
		if (mac_mbuf_tag_init(p, how) != 0) {
			m_tag_free(p);
			return (NULL);
		}
		mac_mbuf_tag_copy(t, p);
	} else
#endif
		bcopy(t + 1, p + 1, t->m_tag_len); /* Copy the data */
	return p;
}