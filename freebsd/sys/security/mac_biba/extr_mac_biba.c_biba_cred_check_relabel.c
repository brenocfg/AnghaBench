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
struct mac_biba {int mb_flags; } ;
struct label {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 int MAC_BIBA_FLAGS_BOTH ; 
 int MAC_BIBA_FLAG_EFFECTIVE ; 
 int MAC_BIBA_FLAG_RANGE ; 
 struct mac_biba* SLOT (struct label*) ; 
 int biba_atmostflags (struct mac_biba*,int) ; 
 scalar_t__ biba_contains_equal (struct mac_biba*) ; 
 int /*<<< orphan*/  biba_effective_in_range (struct mac_biba*,struct mac_biba*) ; 
 int /*<<< orphan*/  biba_range_in_range (struct mac_biba*,struct mac_biba*) ; 
 int biba_subject_privileged (struct mac_biba*) ; 

__attribute__((used)) static int
biba_cred_check_relabel(struct ucred *cred, struct label *newlabel)
{
	struct mac_biba *subj, *new;
	int error;

	subj = SLOT(cred->cr_label);
	new = SLOT(newlabel);

	/*
	 * If there is a Biba label update for the credential, it may
	 * be an update of the effective, range, or both.
	 */
	error = biba_atmostflags(new, MAC_BIBA_FLAGS_BOTH);
	if (error)
		return (error);

	/*
	 * If the Biba label is to be changed, authorize as appropriate.
	 */
	if (new->mb_flags & MAC_BIBA_FLAGS_BOTH) {
		/*
		 * If the change request modifies both the Biba label
		 * effective and range, check that the new effective will be
		 * in the new range.
		 */
		if ((new->mb_flags & MAC_BIBA_FLAGS_BOTH) ==
		    MAC_BIBA_FLAGS_BOTH &&
		    !biba_effective_in_range(new, new))
			return (EINVAL);

		/*
		 * To change the Biba effective label on a credential, the
		 * new effective label must be in the current range.
		 */
		if (new->mb_flags & MAC_BIBA_FLAG_EFFECTIVE &&
		    !biba_effective_in_range(new, subj))
			return (EPERM);

		/*
		 * To change the Biba range on a credential, the new range
		 * label must be in the current range.
		 */
		if (new->mb_flags & MAC_BIBA_FLAG_RANGE &&
		    !biba_range_in_range(new, subj))
			return (EPERM);

		/*
		 * To have EQUAL in any component of the new credential Biba
		 * label, the subject must already have EQUAL in their label.
		 */
		if (biba_contains_equal(new)) {
			error = biba_subject_privileged(subj);
			if (error)
				return (error);
		}
	}

	return (0);
}