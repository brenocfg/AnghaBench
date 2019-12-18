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
struct pfsync_tdb {int dummy; } ;
struct pfsync_pkt {int dummy; } ;
struct mbuf {scalar_t__ m_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  pfsyncs_badlen; } ;

/* Variables and functions */
 TYPE_1__ V_pfsyncstats ; 
 struct mbuf* m_pulldown (struct mbuf*,int,int,int*) ; 
 int /*<<< orphan*/  pfsync_update_net_tdb (struct pfsync_tdb*) ; 

__attribute__((used)) static int
pfsync_in_tdb(struct pfsync_pkt *pkt, struct mbuf *m, int offset, int count)
{
	int len = count * sizeof(struct pfsync_tdb);

#if defined(IPSEC)
	struct pfsync_tdb *tp;
	struct mbuf *mp;
	int offp;
	int i;
	int s;

	mp = m_pulldown(m, offset, len, &offp);
	if (mp == NULL) {
		V_pfsyncstats.pfsyncs_badlen++;
		return (-1);
	}
	tp = (struct pfsync_tdb *)(mp->m_data + offp);

	for (i = 0; i < count; i++)
		pfsync_update_net_tdb(&tp[i]);
#endif

	return (len);
}