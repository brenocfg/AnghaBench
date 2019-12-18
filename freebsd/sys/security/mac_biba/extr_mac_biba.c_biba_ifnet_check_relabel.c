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
struct mac_biba {int dummy; } ;
struct label {int dummy; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_BIBA_FLAGS_BOTH ; 
 struct mac_biba* SLOT (struct label*) ; 
 int biba_atmostflags (struct mac_biba*,int /*<<< orphan*/ ) ; 
 int biba_subject_privileged (struct mac_biba*) ; 

__attribute__((used)) static int
biba_ifnet_check_relabel(struct ucred *cred, struct ifnet *ifp,
    struct label *ifplabel, struct label *newlabel)
{
	struct mac_biba *subj, *new;
	int error;

	subj = SLOT(cred->cr_label);
	new = SLOT(newlabel);

	/*
	 * If there is a Biba label update for the interface, it may be an
	 * update of the effective, range, or both.
	 */
	error = biba_atmostflags(new, MAC_BIBA_FLAGS_BOTH);
	if (error)
		return (error);

	/*
	 * Relabling network interfaces requires Biba privilege.
	 */
	error = biba_subject_privileged(subj);
	if (error)
		return (error);

	return (0);
}