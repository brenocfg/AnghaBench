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
struct mac_lomac {int ml_flags; int /*<<< orphan*/  ml_single; int /*<<< orphan*/  ml_auxsingle; } ;
struct label {int dummy; } ;
struct image_params {int dummy; } ;

/* Variables and functions */
 int MAC_LOMAC_FLAG_AUX ; 
 struct mac_lomac* SLOT (struct label*) ; 
 scalar_t__ lomac_auxsingle_in_range (struct mac_lomac*,struct mac_lomac*) ; 
 int /*<<< orphan*/  lomac_dominate_element (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lomac_dominate_single (struct mac_lomac*,struct mac_lomac*) ; 
 int /*<<< orphan*/  lomac_enabled ; 
 int /*<<< orphan*/  revocation_enabled ; 

__attribute__((used)) static int
lomac_vnode_execve_will_transition(struct ucred *old, struct vnode *vp,
    struct label *vplabel, struct label *interpvplabel,
    struct image_params *imgp, struct label *execlabel)
{
	struct mac_lomac *subj, *obj, *robj;

	if (!lomac_enabled || !revocation_enabled)
		return (0);

	subj = SLOT(old->cr_label);
	obj = SLOT(vplabel);
	robj = interpvplabel != NULL ? SLOT(interpvplabel) : obj;

	return ((robj->ml_flags & MAC_LOMAC_FLAG_AUX &&
	    !lomac_dominate_element(&robj->ml_auxsingle, &subj->ml_single)
	    && lomac_auxsingle_in_range(robj, subj)) ||
	    !lomac_dominate_single(obj, subj));
}