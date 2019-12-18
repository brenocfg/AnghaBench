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
struct pf_mtag {int dummy; } ;
struct mbuf {int dummy; } ;
struct m_tag {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  PACKET_TAG_PF ; 
 int /*<<< orphan*/  bzero (struct m_tag*,int) ; 
 struct m_tag* m_tag_find (struct mbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m_tag_prepend (struct mbuf*,struct m_tag*) ; 
 int /*<<< orphan*/  pf_mtag_z ; 
 struct m_tag* uma_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct pf_mtag *
pf_get_mtag(struct mbuf *m)
{
	struct m_tag *mtag;

	if ((mtag = m_tag_find(m, PACKET_TAG_PF, NULL)) != NULL)
		return ((struct pf_mtag *)(mtag + 1));

	mtag = uma_zalloc(pf_mtag_z, M_NOWAIT);
	if (mtag == NULL)
		return (NULL);
	bzero(mtag + 1, sizeof(struct pf_mtag));
	m_tag_prepend(m, mtag);

	return ((struct pf_mtag *)(mtag + 1));
}