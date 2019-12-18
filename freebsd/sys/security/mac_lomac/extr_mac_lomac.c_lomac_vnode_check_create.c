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
struct vattr {int dummy; } ;
struct ucred {struct label* cr_label; } ;
struct mac_lomac {int ml_flags; int /*<<< orphan*/  ml_auxsingle; int /*<<< orphan*/  ml_single; } ;
struct label {int dummy; } ;
struct componentname {int dummy; } ;

/* Variables and functions */
 int EACCES ; 
 int MAC_LOMAC_FLAG_AUX ; 
 struct mac_lomac* SLOT (struct label*) ; 
 int /*<<< orphan*/  lomac_dominate_element (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lomac_enabled ; 
 int /*<<< orphan*/  lomac_subject_dominate (struct mac_lomac*,struct mac_lomac*) ; 

__attribute__((used)) static int
lomac_vnode_check_create(struct ucred *cred, struct vnode *dvp,
    struct label *dvplabel, struct componentname *cnp, struct vattr *vap)
{
	struct mac_lomac *subj, *obj;

	if (!lomac_enabled)
		return (0);

	subj = SLOT(cred->cr_label);
	obj = SLOT(dvplabel);

	if (!lomac_subject_dominate(subj, obj))
		return (EACCES);
	if (obj->ml_flags & MAC_LOMAC_FLAG_AUX &&
	    !lomac_dominate_element(&subj->ml_single, &obj->ml_auxsingle))
		return (EACCES);

	return (0);
}