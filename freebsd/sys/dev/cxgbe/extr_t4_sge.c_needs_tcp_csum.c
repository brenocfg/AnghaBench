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
struct TYPE_2__ {int csum_flags; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;

/* Variables and functions */
 int CSUM_TCP ; 
 int CSUM_TCP_IPV6 ; 
 int CSUM_TSO ; 
 int /*<<< orphan*/  M_ASSERTPKTHDR (struct mbuf*) ; 

__attribute__((used)) static inline int
needs_tcp_csum(struct mbuf *m)
{

	M_ASSERTPKTHDR(m);
	return (m->m_pkthdr.csum_flags & (CSUM_TCP | CSUM_TCP_IPV6 | CSUM_TSO));
}