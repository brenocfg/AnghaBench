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
struct ucred {int /*<<< orphan*/  cr_label; } ;
struct sysctl_req {int /*<<< orphan*/ * newptr; } ;
struct sysctl_oid {int oid_kind; } ;
struct mac_lomac {int dummy; } ;

/* Variables and functions */
 int CTLFLAG_ANYBODY ; 
 int EACCES ; 
 int EPERM ; 
 struct mac_lomac* SLOT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lomac_enabled ; 
 int /*<<< orphan*/  lomac_subject_dominate_high (struct mac_lomac*) ; 
 scalar_t__ lomac_subject_privileged (struct mac_lomac*) ; 

__attribute__((used)) static int
lomac_system_check_sysctl(struct ucred *cred, struct sysctl_oid *oidp,
    void *arg1, int arg2, struct sysctl_req *req)
{
	struct mac_lomac *subj;

	if (!lomac_enabled)
		return (0);

	subj = SLOT(cred->cr_label);

	/*
	 * Treat sysctl variables without CTLFLAG_ANYBODY flag as lomac/high,
	 * but also require privilege to change them.
	 */
	if (req->newptr != NULL && (oidp->oid_kind & CTLFLAG_ANYBODY) == 0) {
#ifdef notdef
		if (!lomac_subject_dominate_high(subj))
			return (EACCES);
#endif

		if (lomac_subject_privileged(subj))
			return (EPERM);
	}

	return (0);
}