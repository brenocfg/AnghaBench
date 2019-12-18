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
typedef  scalar_t__ uid_t ;
struct cred {scalar_t__ cr_ruid; scalar_t__ cr_euid; scalar_t__ cr_svuid; scalar_t__ cr_issetugid; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int getresuid (scalar_t__*,scalar_t__*,scalar_t__*) ; 
 scalar_t__ issetugid () ; 
 int /*<<< orphan*/  perror (char*) ; 
 int setresuid (scalar_t__,scalar_t__,scalar_t__) ; 
 int setugid (scalar_t__) ; 

__attribute__((used)) static int
cred_set(struct cred *cred)
{
	int error;

	error = setresuid(cred->cr_ruid, cred->cr_euid, cred->cr_svuid);
	if (error)
		return (error);

	error = setugid(cred->cr_issetugid);
	if (error) {
		perror("__setugid");
		return (error);
	}

#ifdef CHECK_CRED_SET
	{
		uid_t ruid, euid, svuid;
		error = getresuid(&ruid, &euid, &svuid);
		if (error) {
			perror("getresuid");
			return (-1);
		}
		assert(ruid == cred->cr_ruid);
		assert(euid == cred->cr_euid);
		assert(svuid == cred->cr_svuid);
		assert(cred->cr_issetugid == issetugid());
	}
#endif /* !CHECK_CRED_SET */

	return (0);
}