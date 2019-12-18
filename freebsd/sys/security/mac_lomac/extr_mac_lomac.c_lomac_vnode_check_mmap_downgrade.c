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
struct vnode {int dummy; } ;
struct ucred {struct label* cr_label; } ;
struct mac_lomac {int dummy; } ;
struct label {int dummy; } ;

/* Variables and functions */
 struct mac_lomac* SLOT (struct label*) ; 
 int VM_PROT_WRITE ; 
 int /*<<< orphan*/  lomac_enabled ; 
 int /*<<< orphan*/  lomac_subject_dominate (struct mac_lomac*,struct mac_lomac*) ; 
 int /*<<< orphan*/  revocation_enabled ; 

__attribute__((used)) static void
lomac_vnode_check_mmap_downgrade(struct ucred *cred, struct vnode *vp,
    struct label *vplabel, /* XXX vm_prot_t */ int *prot)
{
	struct mac_lomac *subj, *obj;

	/*
	 * Rely on the use of open()-time protections to handle
	 * non-revocation cases.
	 */
	if (!lomac_enabled || !revocation_enabled)
		return;

	subj = SLOT(cred->cr_label);
	obj = SLOT(vplabel);

	if (!lomac_subject_dominate(subj, obj))
		*prot &= ~VM_PROT_WRITE;
}