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
struct in_addr {int s_addr; } ;

/* Variables and functions */
#define  IPI_HASHFIELDS_2TUPLE 129 
#define  IPI_HASHFIELDS_4TUPLE 128 
 size_t in_pcbgroup_getbucket (struct inpcbinfo*,int) ; 
 int rss_hash_ip4_2tuple (struct in_addr,struct in_addr) ; 
 int rss_hash_ip4_4tuple (struct in_addr,int,struct in_addr,int) ; 

struct inpcbgroup *
in_pcbgroup_bytuple(struct inpcbinfo *pcbinfo, struct in_addr laddr,
    u_short lport, struct in_addr faddr, u_short fport)
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
		hash = rss_hash_ip4_4tuple(faddr, fport, laddr, lport);
#else
		hash = faddr.s_addr ^ fport;
#endif
		break;

	case IPI_HASHFIELDS_2TUPLE:
#ifdef RSS
		hash = rss_hash_ip4_2tuple(faddr, laddr);
#else
		hash = faddr.s_addr ^ laddr.s_addr;
#endif
		break;

	default:
		hash = 0;
	}
	return (&pcbinfo->ipi_pcbgroups[in_pcbgroup_getbucket(pcbinfo,
	    hash)]);
}