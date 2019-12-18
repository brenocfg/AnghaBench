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
struct mac_mls {int dummy; } ;
struct label {int dummy; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_MLS_FLAGS_BOTH ; 
 struct mac_mls* SLOT (struct label*) ; 
 int mls_atmostflags (struct mac_mls*,int /*<<< orphan*/ ) ; 
 int mls_subject_privileged (struct mac_mls*) ; 

__attribute__((used)) static int
mls_ifnet_check_relabel(struct ucred *cred, struct ifnet *ifp,
    struct label *ifplabel, struct label *newlabel)
{
	struct mac_mls *subj, *new;
	int error;

	subj = SLOT(cred->cr_label);
	new = SLOT(newlabel);

	/*
	 * If there is an MLS label update for the interface, it may be an
	 * update of effective, range, or both.
	 */
	error = mls_atmostflags(new, MAC_MLS_FLAGS_BOTH);
	if (error)
		return (error);

	/*
	 * Relabeling network interfaces requires MLS privilege.
	 */
	return (mls_subject_privileged(subj));
}