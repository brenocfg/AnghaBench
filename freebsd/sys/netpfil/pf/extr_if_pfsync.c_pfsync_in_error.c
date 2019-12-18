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
struct pfsync_pkt {int dummy; } ;
struct mbuf {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pfsyncs_badact; } ;

/* Variables and functions */
 TYPE_1__ V_pfsyncstats ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 

__attribute__((used)) static int
pfsync_in_error(struct pfsync_pkt *pkt, struct mbuf *m, int offset, int count)
{
	V_pfsyncstats.pfsyncs_badact++;

	m_freem(m);
	return (-1);
}