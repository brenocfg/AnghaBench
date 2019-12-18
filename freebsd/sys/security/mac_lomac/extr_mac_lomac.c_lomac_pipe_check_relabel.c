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
struct mac_lomac {int ml_flags; } ;
struct label {int dummy; } ;

/* Variables and functions */
 int EPERM ; 
 int MAC_LOMAC_FLAG_SINGLE ; 
 struct mac_lomac* SLOT (struct label*) ; 
 int lomac_atmostflags (struct mac_lomac*,int) ; 
 scalar_t__ lomac_contains_equal (struct mac_lomac*) ; 
 int /*<<< orphan*/  lomac_single_in_range (struct mac_lomac*,struct mac_lomac*) ; 
 int lomac_subject_privileged (struct mac_lomac*) ; 

__attribute__((used)) static int
lomac_pipe_check_relabel(struct ucred *cred, struct pipepair *pp,
    struct label *pplabel, struct label *newlabel)
{
	struct mac_lomac *subj, *obj, *new;
	int error;

	new = SLOT(newlabel);
	subj = SLOT(cred->cr_label);
	obj = SLOT(pplabel);

	/*
	 * If there is a LOMAC label update for a pipe, it must be a single
	 * update.
	 */
	error = lomac_atmostflags(new, MAC_LOMAC_FLAG_SINGLE);
	if (error)
		return (error);

	/*
	 * To perform a relabel of a pipe (LOMAC label or not), LOMAC must
	 * authorize the relabel.
	 */
	if (!lomac_single_in_range(obj, subj))
		return (EPERM);

	/*
	 * If the LOMAC label is to be changed, authorize as appropriate.
	 */
	if (new->ml_flags & MAC_LOMAC_FLAG_SINGLE) {
		/*
		 * To change the LOMAC label on a pipe, the new pipe label
		 * must be in the subject range.
		 */
		if (!lomac_single_in_range(new, subj))
			return (EPERM);

		/*
		 * To change the LOMAC label on a pipe to be EQUAL, the
		 * subject must have appropriate privilege.
		 */
		if (lomac_contains_equal(new)) {
			error = lomac_subject_privileged(subj);
			if (error)
				return (error);
		}
	}

	return (0);
}