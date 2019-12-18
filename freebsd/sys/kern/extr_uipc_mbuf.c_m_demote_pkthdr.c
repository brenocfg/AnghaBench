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
struct pkthdr {int dummy; } ;
struct mbuf {int /*<<< orphan*/  m_pkthdr; int /*<<< orphan*/  m_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_ASSERTPKTHDR (struct mbuf*) ; 
 int /*<<< orphan*/  M_PKTHDR ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  m_tag_delete_chain (struct mbuf*,int /*<<< orphan*/ *) ; 

void
m_demote_pkthdr(struct mbuf *m)
{

	M_ASSERTPKTHDR(m);

	m_tag_delete_chain(m, NULL);
	m->m_flags &= ~M_PKTHDR;
	bzero(&m->m_pkthdr, sizeof(struct pkthdr));
}