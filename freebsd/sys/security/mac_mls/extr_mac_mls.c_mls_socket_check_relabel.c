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
struct socket {int dummy; } ;
struct mac_mls {int mm_flags; } ;
struct label {int dummy; } ;

/* Variables and functions */
 int EPERM ; 
 int MAC_MLS_FLAG_EFFECTIVE ; 
 struct mac_mls* SLOT (struct label*) ; 
 int /*<<< orphan*/  SOCK_LOCK_ASSERT (struct socket*) ; 
 int mls_atmostflags (struct mac_mls*,int) ; 
 scalar_t__ mls_contains_equal (struct mac_mls*) ; 
 int /*<<< orphan*/  mls_effective_in_range (struct mac_mls*,struct mac_mls*) ; 
 int mls_subject_privileged (struct mac_mls*) ; 

__attribute__((used)) static int
mls_socket_check_relabel(struct ucred *cred, struct socket *so,
    struct label *solabel, struct label *newlabel)
{
	struct mac_mls *subj, *obj, *new;
	int error;

	SOCK_LOCK_ASSERT(so);

	new = SLOT(newlabel);
	subj = SLOT(cred->cr_label);
	obj = SLOT(solabel);

	/*
	 * If there is an MLS label update for the socket, it may be an
	 * update of effective.
	 */
	error = mls_atmostflags(new, MAC_MLS_FLAG_EFFECTIVE);
	if (error)
		return (error);

	/*
	 * To relabel a socket, the old socket effective must be in the
	 * subject range.
	 */
	if (!mls_effective_in_range(obj, subj))
		return (EPERM);

	/*
	 * If the MLS label is to be changed, authorize as appropriate.
	 */
	if (new->mm_flags & MAC_MLS_FLAG_EFFECTIVE) {
		/*
		 * To relabel a socket, the new socket effective must be in
		 * the subject range.
		 */
		if (!mls_effective_in_range(new, subj))
			return (EPERM);

		/*
		 * To change the MLS label on the socket to contain EQUAL,
		 * the subject must have appropriate privilege.
		 */
		if (mls_contains_equal(new)) {
			error = mls_subject_privileged(subj);
			if (error)
				return (error);
		}
	}

	return (0);
}