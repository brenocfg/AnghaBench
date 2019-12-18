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
 int EACCES ; 
 int MAP_SHARED ; 
 struct mac_lomac* SLOT (struct label*) ; 
 int VM_PROT_EXECUTE ; 
 int VM_PROT_READ ; 
 int VM_PROT_WRITE ; 
 int /*<<< orphan*/  lomac_dominate_single (struct mac_lomac*,struct mac_lomac*) ; 
 int /*<<< orphan*/  lomac_enabled ; 
 int /*<<< orphan*/  lomac_subject_dominate (struct mac_lomac*,struct mac_lomac*) ; 
 int maybe_demote (struct mac_lomac*,struct mac_lomac*,char*,char*,struct vnode*) ; 

__attribute__((used)) static int
lomac_vnode_check_mmap(struct ucred *cred, struct vnode *vp,
    struct label *vplabel, int prot, int flags)
{
	struct mac_lomac *subj, *obj;

	/*
	 * Rely on the use of open()-time protections to handle
	 * non-revocation cases.
	 */
	if (!lomac_enabled)
		return (0);

	subj = SLOT(cred->cr_label);
	obj = SLOT(vplabel);

	if (((prot & VM_PROT_WRITE) != 0) && ((flags & MAP_SHARED) != 0)) {
		if (!lomac_subject_dominate(subj, obj))
			return (EACCES);
	}
	if (prot & (VM_PROT_READ | VM_PROT_EXECUTE)) {
		if (!lomac_dominate_single(obj, subj))
			return (maybe_demote(subj, obj, "mapping", "file", vp));
	}

	return (0);
}