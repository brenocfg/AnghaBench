#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vnode {int dummy; } ;
struct ucred {struct label* cr_label; } ;
struct TYPE_2__ {int /*<<< orphan*/  mle_grade; int /*<<< orphan*/  mle_type; } ;
struct mac_lomac {int ml_flags; TYPE_1__ ml_auxsingle; int /*<<< orphan*/  ml_single; } ;
struct label {int dummy; } ;
struct image_params {int dummy; } ;

/* Variables and functions */
 int MAC_LOMAC_FLAG_AUX ; 
 struct mac_lomac* SLOT (struct label*) ; 
 scalar_t__ lomac_auxsingle_in_range (struct mac_lomac*,struct mac_lomac*) ; 
 int /*<<< orphan*/  lomac_copy (struct mac_lomac*,struct mac_lomac*) ; 
 int /*<<< orphan*/  lomac_dominate_element (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lomac_dominate_single (struct mac_lomac*,struct mac_lomac*) ; 
 scalar_t__ lomac_enabled ; 
 int /*<<< orphan*/  lomac_set_single (struct mac_lomac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  maybe_demote (struct mac_lomac*,struct mac_lomac*,char*,char*,struct vnode*) ; 
 scalar_t__ revocation_enabled ; 

__attribute__((used)) static void
lomac_vnode_execve_transition(struct ucred *old, struct ucred *new,
    struct vnode *vp, struct label *vplabel, struct label *interpvplabel,
    struct image_params *imgp, struct label *execlabel)
{
	struct mac_lomac *source, *dest, *obj, *robj;

	source = SLOT(old->cr_label);
	dest = SLOT(new->cr_label);
	obj = SLOT(vplabel);
	robj = interpvplabel != NULL ? SLOT(interpvplabel) : obj;

	lomac_copy(source, dest);
	/*
	 * If there's an auxiliary label on the real object, respect it and
	 * assume that this level should be assumed immediately if a higher
	 * level is currently in place.
	 */
	if (robj->ml_flags & MAC_LOMAC_FLAG_AUX &&
	    !lomac_dominate_element(&robj->ml_auxsingle, &dest->ml_single)
	    && lomac_auxsingle_in_range(robj, dest))
		lomac_set_single(dest, robj->ml_auxsingle.mle_type,
		    robj->ml_auxsingle.mle_grade);
	/*
	 * Restructuring to use the execve transitioning mechanism instead of
	 * the normal demotion mechanism here would be difficult, so just
	 * copy the label over and perform standard demotion.  This is also
	 * non-optimal because it will result in the intermediate label "new"
	 * being created and immediately recycled.
	 */
	if (lomac_enabled && revocation_enabled &&
	    !lomac_dominate_single(obj, source))
		(void)maybe_demote(source, obj, "executing", "file", vp);
}