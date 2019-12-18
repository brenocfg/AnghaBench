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
struct mac_biba {int mb_flags; } ;
struct label {int dummy; } ;

/* Variables and functions */
 int EPERM ; 
 int MAC_BIBA_FLAG_EFFECTIVE ; 
 struct mac_biba* SLOT (struct label*) ; 
 int /*<<< orphan*/  SOCK_LOCK_ASSERT (struct socket*) ; 
 int biba_atmostflags (struct mac_biba*,int) ; 
 scalar_t__ biba_contains_equal (struct mac_biba*) ; 
 int /*<<< orphan*/  biba_effective_in_range (struct mac_biba*,struct mac_biba*) ; 
 int biba_subject_privileged (struct mac_biba*) ; 

__attribute__((used)) static int
biba_socket_check_relabel(struct ucred *cred, struct socket *so,
    struct label *solabel, struct label *newlabel)
{
	struct mac_biba *subj, *obj, *new;
	int error;

	SOCK_LOCK_ASSERT(so);

	new = SLOT(newlabel);
	subj = SLOT(cred->cr_label);
	obj = SLOT(solabel);

	/*
	 * If there is a Biba label update for the socket, it may be an
	 * update of effective.
	 */
	error = biba_atmostflags(new, MAC_BIBA_FLAG_EFFECTIVE);
	if (error)
		return (error);

	/*
	 * To relabel a socket, the old socket effective must be in the
	 * subject range.
	 */
	if (!biba_effective_in_range(obj, subj))
		return (EPERM);

	/*
	 * If the Biba label is to be changed, authorize as appropriate.
	 */
	if (new->mb_flags & MAC_BIBA_FLAG_EFFECTIVE) {
		/*
		 * To relabel a socket, the new socket effective must be in
		 * the subject range.
		 */
		if (!biba_effective_in_range(new, subj))
			return (EPERM);

		/*
		 * To change the Biba label on the socket to contain EQUAL,
		 * the subject must have appropriate privilege.
		 */
		if (biba_contains_equal(new)) {
			error = biba_subject_privileged(subj);
			if (error)
				return (error);
		}
	}

	return (0);
}