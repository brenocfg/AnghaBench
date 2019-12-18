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
struct TYPE_2__ {unsigned int len; } ;
struct mbuf {unsigned int m_len; TYPE_1__ m_pkthdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCLGET (struct mbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MGETHDR (struct mbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MT_DATA ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  bcopy (void*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  caddr_t ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  mtod (struct mbuf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mbuf *makembuf (void *buf, unsigned len)
{
	struct mbuf *m;

	MGETHDR (m, M_NOWAIT, MT_DATA);
	if (! m)
		return 0;
	if (!(MCLGET (m, M_NOWAIT))) {
		m_freem (m);
		return 0;
	}
	m->m_pkthdr.len = m->m_len = len;
	bcopy (buf, mtod (m, caddr_t), len);
	return m;
}