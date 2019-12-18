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
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  int u_int16_t ;
struct pf_addr {int /*<<< orphan*/ * addr16; } ;
struct TYPE_2__ {int csum_flags; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;
typedef  int /*<<< orphan*/  sa_family_t ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int CSUM_DELAY_DATA ; 
 int CSUM_DELAY_DATA_IPV6 ; 
 int /*<<< orphan*/  PF_ACPY (struct pf_addr*,struct pf_addr*,int /*<<< orphan*/ ) ; 
 int pf_cksum_fixup (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pf_proto_cksum_fixup (struct mbuf*,int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pf_change_ap(struct mbuf *m, struct pf_addr *a, u_int16_t *p, u_int16_t *ic,
        u_int16_t *pc, struct pf_addr *an, u_int16_t pn, u_int8_t u,
        sa_family_t af)
{
	struct pf_addr	ao;
	u_int16_t	po = *p;

	PF_ACPY(&ao, a, af);
	PF_ACPY(a, an, af);

	if (m->m_pkthdr.csum_flags & (CSUM_DELAY_DATA | CSUM_DELAY_DATA_IPV6))
		*pc = ~*pc;

	*p = pn;

	switch (af) {
#ifdef INET
	case AF_INET:
		*ic = pf_cksum_fixup(pf_cksum_fixup(*ic,
		    ao.addr16[0], an->addr16[0], 0),
		    ao.addr16[1], an->addr16[1], 0);
		*p = pn;

		*pc = pf_cksum_fixup(pf_cksum_fixup(*pc,
		    ao.addr16[0], an->addr16[0], u),
		    ao.addr16[1], an->addr16[1], u);

		*pc = pf_proto_cksum_fixup(m, *pc, po, pn, u);
		break;
#endif /* INET */
#ifdef INET6
	case AF_INET6:
		*pc = pf_cksum_fixup(pf_cksum_fixup(pf_cksum_fixup(
		    pf_cksum_fixup(pf_cksum_fixup(pf_cksum_fixup(
		    pf_cksum_fixup(pf_cksum_fixup(*pc,
		    ao.addr16[0], an->addr16[0], u),
		    ao.addr16[1], an->addr16[1], u),
		    ao.addr16[2], an->addr16[2], u),
		    ao.addr16[3], an->addr16[3], u),
		    ao.addr16[4], an->addr16[4], u),
		    ao.addr16[5], an->addr16[5], u),
		    ao.addr16[6], an->addr16[6], u),
		    ao.addr16[7], an->addr16[7], u);

		*pc = pf_proto_cksum_fixup(m, *pc, po, pn, u);
		break;
#endif /* INET6 */
	}

	if (m->m_pkthdr.csum_flags & (CSUM_DELAY_DATA | 
	    CSUM_DELAY_DATA_IPV6)) {
		*pc = ~*pc;
		if (! *pc)
			*pc = 0xffff;
	}
}