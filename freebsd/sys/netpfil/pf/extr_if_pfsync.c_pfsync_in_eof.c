#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pfsync_pkt {int dummy; } ;
struct TYPE_3__ {int len; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;
struct TYPE_4__ {int /*<<< orphan*/  pfsyncs_badlen; } ;

/* Variables and functions */
 TYPE_2__ V_pfsyncstats ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 

__attribute__((used)) static int
pfsync_in_eof(struct pfsync_pkt *pkt, struct mbuf *m, int offset, int count)
{
	/* check if we are at the right place in the packet */
	if (offset != m->m_pkthdr.len)
		V_pfsyncstats.pfsyncs_badlen++;

	/* we're done. free and let the caller return */
	m_freem(m);
	return (-1);
}