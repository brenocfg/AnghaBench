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
struct mbuf {int dummy; } ;
struct m_tag {scalar_t__ m_tag_id; scalar_t__ m_tag_cookie; } ;
struct dn_pkt_tag {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  D (char*) ; 
 scalar_t__ DN_AQM_MTAG_TS ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ MTAG_ABI_COMPAT ; 
 scalar_t__ PACKET_TAG_DUMMYNET ; 
 int /*<<< orphan*/  m_tag_delete (struct mbuf*,struct m_tag*) ; 
 struct m_tag* m_tag_first (struct mbuf*) ; 

struct dn_pkt_tag *
dn_tag_get(struct mbuf *m)
{
	struct m_tag *mtag = m_tag_first(m);
#ifdef NEW_AQM
	/* XXX: to skip ts m_tag. For Debugging only*/
	if (mtag != NULL && mtag->m_tag_id == DN_AQM_MTAG_TS) {
		m_tag_delete(m,mtag); 
		mtag = m_tag_first(m);
		D("skip TS tag");
	}
#endif
	KASSERT(mtag != NULL &&
	    mtag->m_tag_cookie == MTAG_ABI_COMPAT &&
	    mtag->m_tag_id == PACKET_TAG_DUMMYNET,
	    ("packet on dummynet queue w/o dummynet tag!"));
	return (struct dn_pkt_tag *)(mtag+1);
}