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
struct ucred {scalar_t__ cr_rgid; scalar_t__ cr_ruid; } ;

/* Variables and functions */
 int ESRCH ; 
 int /*<<< orphan*/  PRIV_SEEOTHERUIDS ; 
 scalar_t__ groupmember (scalar_t__,struct ucred*) ; 
 scalar_t__ primarygroup_enabled ; 
 scalar_t__ priv_check_cred (struct ucred*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seeotheruids_enabled ; 
 scalar_t__ specificgid ; 
 scalar_t__ specificgid_enabled ; 
 scalar_t__ suser_privileged ; 

__attribute__((used)) static int
seeotheruids_check(struct ucred *cr1, struct ucred *cr2)
{

	if (!seeotheruids_enabled)
		return (0);

	if (primarygroup_enabled) {
		if (cr1->cr_rgid == cr2->cr_rgid)
			return (0);
	}

	if (specificgid_enabled) {
		if (cr1->cr_rgid == specificgid ||
		    groupmember(specificgid, cr1))
			return (0);
	}

	if (cr1->cr_ruid == cr2->cr_ruid)
		return (0);

	if (suser_privileged) {
		if (priv_check_cred(cr1, PRIV_SEEOTHERUIDS) == 0)
			return (0);
	}

	return (ESRCH);
}