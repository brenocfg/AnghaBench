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
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  int /*<<< orphan*/  u_int32_t ;
struct mbuf {int dummy; } ;
struct ip6_hbh {int ip6h_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  IP6STAT_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  caddr_t ; 
 scalar_t__ ip6_process_hopopts (struct mbuf*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ip6s_exthdrtoolong ; 
 struct mbuf* m_pullup (struct mbuf*,int) ; 
 scalar_t__ mtod (struct mbuf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ip6_hopopts_input(u_int32_t *plenp, u_int32_t *rtalertp,
    struct mbuf **mp, int *offp)
{
	struct mbuf *m = *mp;
	int off = *offp, hbhlen;
	struct ip6_hbh *hbh;

	/* validation of the length of the header */
	m = m_pullup(m, off + sizeof(*hbh));
	if (m == NULL) {
		IP6STAT_INC(ip6s_exthdrtoolong);
		*mp = NULL;
		return (-1);
	}
	hbh = (struct ip6_hbh *)(mtod(m, caddr_t) + off);
	hbhlen = (hbh->ip6h_len + 1) << 3;

	m = m_pullup(m, off + hbhlen);
	if (m == NULL) {
		IP6STAT_INC(ip6s_exthdrtoolong);
		*mp = NULL;
		return (-1);
	}
	hbh = (struct ip6_hbh *)(mtod(m, caddr_t) + off);
	off += hbhlen;
	hbhlen -= sizeof(struct ip6_hbh);
	if (ip6_process_hopopts(m, (u_int8_t *)hbh + sizeof(struct ip6_hbh),
				hbhlen, rtalertp, plenp) < 0) {
		*mp = NULL;
		return (-1);
	}

	*offp = off;
	*mp = m;
	return (0);
}