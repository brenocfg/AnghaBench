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
struct mac_lomac {int ml_flags; } ;
struct label {int dummy; } ;

/* Variables and functions */
 int EPERM ; 
 int MAC_LOMAC_FLAG_SINGLE ; 
 struct mac_lomac* SLOT (struct label*) ; 
 int /*<<< orphan*/  SOCK_LOCK_ASSERT (struct socket*) ; 
 int lomac_atmostflags (struct mac_lomac*,int) ; 
 scalar_t__ lomac_contains_equal (struct mac_lomac*) ; 
 int /*<<< orphan*/  lomac_single_in_range (struct mac_lomac*,struct mac_lomac*) ; 
 int lomac_subject_privileged (struct mac_lomac*) ; 

__attribute__((used)) static int
lomac_socket_check_relabel(struct ucred *cred, struct socket *so,
    struct label *solabel, struct label *newlabel)
{
	struct mac_lomac *subj, *obj, *new;
	int error;

	SOCK_LOCK_ASSERT(so);

	new = SLOT(newlabel);
	subj = SLOT(cred->cr_label);
	obj = SLOT(solabel);

	/*
	 * If there is a LOMAC label update for the socket, it may be an
	 * update of single.
	 */
	error = lomac_atmostflags(new, MAC_LOMAC_FLAG_SINGLE);
	if (error)
		return (error);

	/*
	 * To relabel a socket, the old socket single must be in the subject
	 * range.
	 */
	if (!lomac_single_in_range(obj, subj))
		return (EPERM);

	/*
	 * If the LOMAC label is to be changed, authorize as appropriate.
	 */
	if (new->ml_flags & MAC_LOMAC_FLAG_SINGLE) {
		/*
		 * To relabel a socket, the new socket single must be in the
		 * subject range.
		 */
		if (!lomac_single_in_range(new, subj))
			return (EPERM);

		/*
		 * To change the LOMAC label on the socket to contain EQUAL,
		 * the subject must have appropriate privilege.
		 */
		if (lomac_contains_equal(new)) {
			error = lomac_subject_privileged(subj);
			if (error)
				return (error);
		}
	}

	return (0);
}