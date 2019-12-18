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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u_int ;
struct TYPE_2__ {int /*<<< orphan*/  flowid; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_ASSERTPKTHDR (struct mbuf*) ; 
 int /*<<< orphan*/  M_HASHTYPE_GET (struct mbuf*) ; 
 int /*<<< orphan*/  M_HASHTYPE_SET (struct mbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NETISR_CPUID_NONE ; 
 int /*<<< orphan*/  RSS_HASH_PKT_INGRESS ; 
 int /*<<< orphan*/  rss_hash2cpuid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rss_mbuf_software_hash_v6 (struct mbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

struct mbuf *
rss_soft_m2cpuid_v6(struct mbuf *m, uintptr_t source, u_int *cpuid)
{
	uint32_t hash_val, hash_type;
	int ret;

	M_ASSERTPKTHDR(m);

	ret = rss_mbuf_software_hash_v6(m, RSS_HASH_PKT_INGRESS,
	    &hash_val, &hash_type);
	if (ret > 0) {
		/* mbuf has a valid hash already; don't need to modify it */
		*cpuid = rss_hash2cpuid(m->m_pkthdr.flowid, M_HASHTYPE_GET(m));
	} else if (ret == 0) {
		/* hash was done; update */
		m->m_pkthdr.flowid = hash_val;
		M_HASHTYPE_SET(m, hash_type);
		*cpuid = rss_hash2cpuid(m->m_pkthdr.flowid, M_HASHTYPE_GET(m));
	} else { /* ret < 0 */
		/* no hash was done */
		*cpuid = NETISR_CPUID_NONE;
	}
	return (m);
}