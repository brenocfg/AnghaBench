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
struct ucred {struct label* cr_label; } ;
struct mac_lomac {int ml_flags; } ;
struct label {int dummy; } ;

/* Variables and functions */
 int EPERM ; 
 int MAC_LOMAC_FLAGS_BOTH ; 
 int MAC_LOMAC_FLAG_RANGE ; 
 int MAC_LOMAC_FLAG_SINGLE ; 
 struct mac_lomac* SLOT (struct label*) ; 
 int lomac_atmostflags (struct mac_lomac*,int) ; 
 scalar_t__ lomac_contains_equal (struct mac_lomac*) ; 
 int /*<<< orphan*/  lomac_copy_range (struct mac_lomac*,struct mac_lomac*) ; 
 int /*<<< orphan*/  lomac_copy_single (struct mac_lomac*,struct mac_lomac*) ; 
 int /*<<< orphan*/  lomac_range_in_range (struct mac_lomac*,struct mac_lomac*) ; 
 int /*<<< orphan*/  lomac_single_in_range (struct mac_lomac*,struct mac_lomac*) ; 
 int lomac_subject_privileged (struct mac_lomac*) ; 

__attribute__((used)) static int
lomac_cred_check_relabel(struct ucred *cred, struct label *newlabel)
{
	struct mac_lomac *subj, *new;
	int error;

	subj = SLOT(cred->cr_label);
	new = SLOT(newlabel);

	/*
	 * If there is a LOMAC label update for the credential, it may be an
	 * update of the single, range, or both.
	 */
	error = lomac_atmostflags(new, MAC_LOMAC_FLAGS_BOTH);
	if (error)
		return (error);

	/*
	 * If the LOMAC label is to be changed, authorize as appropriate.
	 */
	if (new->ml_flags & MAC_LOMAC_FLAGS_BOTH) {
		/*
		 * Fill in the missing parts from the previous label.
		 */
		if ((new->ml_flags & MAC_LOMAC_FLAG_SINGLE) == 0)
			lomac_copy_single(subj, new);
		if ((new->ml_flags & MAC_LOMAC_FLAG_RANGE) == 0)
			lomac_copy_range(subj, new);

		/*
		 * To change the LOMAC range on a credential, the new range
		 * label must be in the current range.
		 */
		if (!lomac_range_in_range(new, subj))
			return (EPERM);

		/*
		 * To change the LOMAC single label on a credential, the new
		 * single label must be in the new range.  Implicitly from
		 * the previous check, the new single is in the old range.
		 */
		if (!lomac_single_in_range(new, new))
			return (EPERM);

		/*
		 * To have EQUAL in any component of the new credential LOMAC
		 * label, the subject must already have EQUAL in their label.
		 */
		if (lomac_contains_equal(new)) {
			error = lomac_subject_privileged(subj);
			if (error)
				return (error);
		}

		/*
		 * XXXMAC: Additional consistency tests regarding the single
		 * and range of the new label might be performed here.
		 */
	}

	return (0);
}