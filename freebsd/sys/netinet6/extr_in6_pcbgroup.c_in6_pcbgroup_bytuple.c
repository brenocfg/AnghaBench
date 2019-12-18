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
typedef  int uint32_t ;
typedef  int u_short ;
struct inpcbinfo {int ipi_hashfields; struct inpcbgroup* ipi_pcbgroups; } ;
struct inpcbgroup {int dummy; } ;
struct in6_addr {int* s6_addr32; } ;

/* Variables and functions */
#define  IPI_HASHFIELDS_2TUPLE 129 
#define  IPI_HASHFIELDS_4TUPLE 128 
 size_t in6_pcbgroup_getbucket (struct inpcbinfo*,int) ; 
 int rss_hash_ip6_2tuple (struct in6_addr const*,struct in6_addr const*) ; 
 int rss_hash_ip6_4tuple (struct in6_addr const*,int,struct in6_addr const*,int) ; 

struct inpcbgroup *
in6_pcbgroup_bytuple(struct inpcbinfo *pcbinfo, const struct in6_addr *laddrp,
    u_short lport, const struct in6_addr *faddrp, u_short fport)
{
	uint32_t hash;

	/*
	 * RSS note: we pass foreign addr/port as source, and local addr/port
	 * as destination, as we want to align with what the hardware is
	 * doing.
	 */
	switch (pcbinfo->ipi_hashfields) {
	case IPI_HASHFIELDS_4TUPLE:
#ifdef RSS
		hash = rss_hash_ip6_4tuple(faddrp, fport, laddrp, lport);
#else
		hash = faddrp->s6_addr32[3] ^ fport;
#endif
		break;

	case IPI_HASHFIELDS_2TUPLE:
#ifdef RSS
		hash = rss_hash_ip6_2tuple(faddrp, laddrp);
#else
		hash = faddrp->s6_addr32[3] ^ laddrp->s6_addr32[3];
#endif
		break;

	default:
		hash = 0;
	}
	return (&pcbinfo->ipi_pcbgroups[in6_pcbgroup_getbucket(pcbinfo,
	    hash)]);
}