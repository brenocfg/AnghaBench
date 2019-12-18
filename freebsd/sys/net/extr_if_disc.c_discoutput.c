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
typedef  scalar_t__ u_int32_t ;
struct sockaddr {scalar_t__ sa_family; int /*<<< orphan*/  sa_data; } ;
struct route {int dummy; } ;
struct TYPE_2__ {int len; struct ifnet* rcvif; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;
struct ifnet {int /*<<< orphan*/  if_bpf; } ;
typedef  int /*<<< orphan*/  af ;

/* Variables and functions */
 scalar_t__ AF_UNSPEC ; 
 int /*<<< orphan*/  IFCOUNTER_OBYTES ; 
 int /*<<< orphan*/  IFCOUNTER_OPACKETS ; 
 int /*<<< orphan*/  M_ASSERTPKTHDR (struct mbuf*) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  bpf_mtap2 (int /*<<< orphan*/ ,scalar_t__*,int,struct mbuf*) ; 
 scalar_t__ bpf_peers_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 

__attribute__((used)) static int
discoutput(struct ifnet *ifp, struct mbuf *m, const struct sockaddr *dst,
    struct route *ro)
{
	u_int32_t af;

	M_ASSERTPKTHDR(m);

	/* BPF writes need to be handled specially. */
	if (dst->sa_family == AF_UNSPEC)
		bcopy(dst->sa_data, &af, sizeof(af));
	else
		af = dst->sa_family;

	if (bpf_peers_present(ifp->if_bpf))
		bpf_mtap2(ifp->if_bpf, &af, sizeof(af), m);

	m->m_pkthdr.rcvif = ifp;

	if_inc_counter(ifp, IFCOUNTER_OPACKETS, 1);
	if_inc_counter(ifp, IFCOUNTER_OBYTES, m->m_pkthdr.len);

	m_freem(m);
	return (0);
}