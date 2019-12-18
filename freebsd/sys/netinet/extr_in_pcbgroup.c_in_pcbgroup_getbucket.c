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
typedef  int u_int ;
struct inpcbinfo {int ipi_npcbgroups; } ;

/* Variables and functions */
 int rss_getbucket (int) ; 

__attribute__((used)) static __inline u_int
in_pcbgroup_getbucket(struct inpcbinfo *pcbinfo, uint32_t hash)
{

#ifdef RSS
	return (rss_getbucket(hash));
#else
	return (hash % pcbinfo->ipi_npcbgroups);
#endif
}