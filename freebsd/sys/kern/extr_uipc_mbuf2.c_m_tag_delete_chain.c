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
struct TYPE_2__ {int /*<<< orphan*/  tags; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;
struct m_tag {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (struct mbuf*,char*) ; 
 struct m_tag* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 struct m_tag* SLIST_NEXT (struct m_tag*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_tag_delete (struct mbuf*,struct m_tag*) ; 
 int /*<<< orphan*/  m_tag_link ; 

void
m_tag_delete_chain(struct mbuf *m, struct m_tag *t)
{
	struct m_tag *p, *q;

	KASSERT(m, ("m_tag_delete_chain: null mbuf"));
	if (t != NULL)
		p = t;
	else
		p = SLIST_FIRST(&m->m_pkthdr.tags);
	if (p == NULL)
		return;
	while ((q = SLIST_NEXT(p, m_tag_link)) != NULL)
		m_tag_delete(m, q);
	m_tag_delete(m, p);
}