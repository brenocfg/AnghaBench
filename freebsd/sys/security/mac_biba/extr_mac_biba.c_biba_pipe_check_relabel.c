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
struct pipepair {int dummy; } ;
struct mac_biba {int mb_flags; } ;
struct label {int dummy; } ;

/* Variables and functions */
 int EPERM ; 
 int MAC_BIBA_FLAG_EFFECTIVE ; 
 struct mac_biba* SLOT (struct label*) ; 
 int biba_atmostflags (struct mac_biba*,int) ; 
 scalar_t__ biba_contains_equal (struct mac_biba*) ; 
 int /*<<< orphan*/  biba_effective_in_range (struct mac_biba*,struct mac_biba*) ; 
 int biba_subject_privileged (struct mac_biba*) ; 

__attribute__((used)) static int
biba_pipe_check_relabel(struct ucred *cred, struct pipepair *pp,
    struct label *pplabel, struct label *newlabel)
{
	struct mac_biba *subj, *obj, *new;
	int error;

	new = SLOT(newlabel);
	subj = SLOT(cred->cr_label);
	obj = SLOT(pplabel);

	/*
	 * If there is a Biba label update for a pipe, it must be a effective
	 * update.
	 */
	error = biba_atmostflags(new, MAC_BIBA_FLAG_EFFECTIVE);
	if (error)
		return (error);

	/*
	 * To perform a relabel of a pipe (Biba label or not), Biba must
	 * authorize the relabel.
	 */
	if (!biba_effective_in_range(obj, subj))
		return (EPERM);

	/*
	 * If the Biba label is to be changed, authorize as appropriate.
	 */
	if (new->mb_flags & MAC_BIBA_FLAG_EFFECTIVE) {
		/*
		 * To change the Biba label on a pipe, the new pipe label
		 * must be in the subject range.
		 */
		if (!biba_effective_in_range(new, subj))
			return (EPERM);

		/*
		 * To change the Biba label on a pipe to be EQUAL, the
		 * subject must have appropriate privilege.
		 */
		if (biba_contains_equal(new)) {
			error = biba_subject_privileged(subj);
			if (error)
				return (error);
		}
	}

	return (0);
}