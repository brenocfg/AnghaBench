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
struct mac_mls {int mm_flags; } ;
struct label {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 int MAC_MLS_FLAGS_BOTH ; 
 int MAC_MLS_FLAG_EFFECTIVE ; 
 int MAC_MLS_FLAG_RANGE ; 
 struct mac_mls* SLOT (struct label*) ; 
 int mls_atmostflags (struct mac_mls*,int) ; 
 scalar_t__ mls_contains_equal (struct mac_mls*) ; 
 int /*<<< orphan*/  mls_effective_in_range (struct mac_mls*,struct mac_mls*) ; 
 int /*<<< orphan*/  mls_range_in_range (struct mac_mls*,struct mac_mls*) ; 
 int mls_subject_privileged (struct mac_mls*) ; 

__attribute__((used)) static int
mls_cred_check_relabel(struct ucred *cred, struct label *newlabel)
{
	struct mac_mls *subj, *new;
	int error;

	subj = SLOT(cred->cr_label);
	new = SLOT(newlabel);

	/*
	 * If there is an MLS label update for the credential, it may be an
	 * update of effective, range, or both.
	 */
	error = mls_atmostflags(new, MAC_MLS_FLAGS_BOTH);
	if (error)
		return (error);

	/*
	 * If the MLS label is to be changed, authorize as appropriate.
	 */
	if (new->mm_flags & MAC_MLS_FLAGS_BOTH) {
		/*
		 * If the change request modifies both the MLS label
		 * effective and range, check that the new effective will be
		 * in the new range.
		 */
		if ((new->mm_flags & MAC_MLS_FLAGS_BOTH) ==
		    MAC_MLS_FLAGS_BOTH && !mls_effective_in_range(new, new))
			return (EINVAL);

		/*
		 * To change the MLS effective label on a credential, the new
		 * effective label must be in the current range.
		 */
		if (new->mm_flags & MAC_MLS_FLAG_EFFECTIVE &&
		    !mls_effective_in_range(new, subj))
			return (EPERM);

		/*
		 * To change the MLS range label on a credential, the new
		 * range must be in the current range.
		 */
		if (new->mm_flags & MAC_MLS_FLAG_RANGE &&
		    !mls_range_in_range(new, subj))
			return (EPERM);

		/*
		 * To have EQUAL in any component of the new credential MLS
		 * label, the subject must already have EQUAL in their label.
		 */
		if (mls_contains_equal(new)) {
			error = mls_subject_privileged(subj);
			if (error)
				return (error);
		}
	}

	return (0);
}