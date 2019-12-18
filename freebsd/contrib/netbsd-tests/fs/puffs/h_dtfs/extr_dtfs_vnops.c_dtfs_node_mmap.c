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
typedef  int vm_prot_t ;
struct puffs_usermount {int dummy; } ;
struct puffs_cred {int dummy; } ;
struct dtfs_mount {int dtm_allowprot; } ;

/* Variables and functions */
 int EACCES ; 
 struct dtfs_mount* puffs_getspecific (struct puffs_usermount*) ; 

int
dtfs_node_mmap(struct puffs_usermount *pu, void *opc, vm_prot_t prot,
	const struct puffs_cred *pcr)
{
	struct dtfs_mount *dtm = puffs_getspecific(pu);

	if ((dtm->dtm_allowprot & prot) != prot)
		return EACCES;

	return 0;
}