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
typedef  int /*<<< orphan*/  u_int ;
struct TYPE_2__ {int /*<<< orphan*/  rcvif; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpuid_from_ifp (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mbuf *
epair_nh_m2cpuid(struct mbuf *m, uintptr_t source, u_int *cpuid)
{

	*cpuid = cpuid_from_ifp(m->m_pkthdr.rcvif);

	return (m);
}