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
struct TYPE_2__ {int /*<<< orphan*/  flowid; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_ASSERTPKTHDR (struct mbuf*) ; 
 int /*<<< orphan*/  M_HASHTYPE_GET (struct mbuf*) ; 
 int /*<<< orphan*/  rss_hash2cpuid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct mbuf *
rss_m2cpuid(struct mbuf *m, uintptr_t source, u_int *cpuid)
{

	M_ASSERTPKTHDR(m);
	*cpuid = rss_hash2cpuid(m->m_pkthdr.flowid, M_HASHTYPE_GET(m));
	return (m);
}