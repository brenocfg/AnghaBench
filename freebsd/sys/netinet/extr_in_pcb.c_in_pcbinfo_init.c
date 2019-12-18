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
typedef  int /*<<< orphan*/  uma_init ;
typedef  int /*<<< orphan*/  u_int ;
struct inpcbinfo {int /*<<< orphan*/  ipi_zone; int /*<<< orphan*/  ipi_lbgrouphashmask; void* ipi_lbgrouphashbase; int /*<<< orphan*/  ipi_porthashmask; void* ipi_porthashbase; int /*<<< orphan*/  ipi_hashmask; void* ipi_hashbase; scalar_t__ ipi_count; struct inpcbhead* ipi_listhead; int /*<<< orphan*/  ipi_vnet; } ;
struct inpcbhead {int dummy; } ;
struct inpcb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CK_LIST_INIT (struct inpcbhead*) ; 
 int /*<<< orphan*/  INP_HASH_LOCK_INIT (struct inpcbinfo*,char*) ; 
 int /*<<< orphan*/  INP_INFO_LOCK_INIT (struct inpcbinfo*,char const*) ; 
 int /*<<< orphan*/  INP_LIST_LOCK_INIT (struct inpcbinfo*,char*) ; 
 scalar_t__ IPPORT_MAX ; 
 int /*<<< orphan*/  M_PCB ; 
 int /*<<< orphan*/  UMA_ALIGN_PTR ; 
 int /*<<< orphan*/  curvnet ; 
 void* hashinit (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int imin (int,scalar_t__) ; 
 int /*<<< orphan*/  in_pcbgroup_init (struct inpcbinfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  inpcb_fini ; 
 int /*<<< orphan*/  maxsockets ; 
 int /*<<< orphan*/  uma_zcreate (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uma_zone_set_max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uma_zone_set_warning (int /*<<< orphan*/ ,char*) ; 

void
in_pcbinfo_init(struct inpcbinfo *pcbinfo, const char *name,
    struct inpcbhead *listhead, int hash_nelements, int porthash_nelements,
    char *inpcbzone_name, uma_init inpcbzone_init, u_int hashfields)
{

	porthash_nelements = imin(porthash_nelements, IPPORT_MAX + 1);

	INP_INFO_LOCK_INIT(pcbinfo, name);
	INP_HASH_LOCK_INIT(pcbinfo, "pcbinfohash");	/* XXXRW: argument? */
	INP_LIST_LOCK_INIT(pcbinfo, "pcbinfolist");
#ifdef VIMAGE
	pcbinfo->ipi_vnet = curvnet;
#endif
	pcbinfo->ipi_listhead = listhead;
	CK_LIST_INIT(pcbinfo->ipi_listhead);
	pcbinfo->ipi_count = 0;
	pcbinfo->ipi_hashbase = hashinit(hash_nelements, M_PCB,
	    &pcbinfo->ipi_hashmask);
	pcbinfo->ipi_porthashbase = hashinit(porthash_nelements, M_PCB,
	    &pcbinfo->ipi_porthashmask);
	pcbinfo->ipi_lbgrouphashbase = hashinit(porthash_nelements, M_PCB,
	    &pcbinfo->ipi_lbgrouphashmask);
#ifdef PCBGROUP
	in_pcbgroup_init(pcbinfo, hashfields, hash_nelements);
#endif
	pcbinfo->ipi_zone = uma_zcreate(inpcbzone_name, sizeof(struct inpcb),
	    NULL, NULL, inpcbzone_init, inpcb_fini, UMA_ALIGN_PTR, 0);
	uma_zone_set_max(pcbinfo->ipi_zone, maxsockets);
	uma_zone_set_warning(pcbinfo->ipi_zone,
	    "kern.ipc.maxsockets limit reached");
}