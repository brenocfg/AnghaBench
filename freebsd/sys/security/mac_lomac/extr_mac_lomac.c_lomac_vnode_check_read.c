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
 int /*<<< orphan*/  lomac_dominate_single (struct mac_lomac*,struct mac_lomac*) ; 
 int /*<<< orphan*/  lomac_enabled ; 
 int maybe_demote (struct mac_lomac*,struct mac_lomac*,char*,char*,struct vnode*) ; 
 int /*<<< orphan*/  revocation_enabled ; 

__attribute__((used)) static int
lomac_vnode_check_read(struct ucred *active_cred, struct ucred *file_cred,
    struct vnode *vp, struct label *vplabel)
{
	struct mac_lomac *subj, *obj;

	if (!lomac_enabled || !revocation_enabled)
		return (0);

	subj = SLOT(active_cred->cr_label);
	obj = SLOT(vplabel);

	if (!lomac_dominate_single(obj, subj))
		return (maybe_demote(subj, obj, "reading", "file", vp));

	return (0);
}