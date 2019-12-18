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
struct netfront_rxq {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  len; } ;
struct mbuf {TYPE_1__ m_pkthdr; int /*<<< orphan*/  m_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  MJUMPAGESIZE ; 
 int /*<<< orphan*/  MT_DATA ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  M_PKTHDR ; 
 struct mbuf* m_getjcl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mbuf *
xn_alloc_one_rx_buffer(struct netfront_rxq *rxq)
{
	struct mbuf *m;

	m = m_getjcl(M_NOWAIT, MT_DATA, M_PKTHDR, MJUMPAGESIZE);
	if (m == NULL)
		return NULL;
	m->m_len = m->m_pkthdr.len = MJUMPAGESIZE;

	return (m);
}