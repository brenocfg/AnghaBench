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
struct TYPE_2__ {scalar_t__ len; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_ASSERTPKTHDR (struct mbuf*) ; 
 int /*<<< orphan*/  m_cat (struct mbuf*,struct mbuf*) ; 
 int /*<<< orphan*/  m_demote (struct mbuf*,int,int /*<<< orphan*/ ) ; 

void
m_catpkt(struct mbuf *m, struct mbuf *n)
{

	M_ASSERTPKTHDR(m);
	M_ASSERTPKTHDR(n);

	m->m_pkthdr.len += n->m_pkthdr.len;
	m_demote(n, 1, 0);

	m_cat(m, n);
}