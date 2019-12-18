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
struct ucred {int dummy; } ;
struct ksem {int /*<<< orphan*/  ks_gid; int /*<<< orphan*/  ks_uid; int /*<<< orphan*/  ks_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  PRIV_SEM_WRITE ; 
 int VREAD ; 
 int /*<<< orphan*/  VREG ; 
 int VWRITE ; 
 int priv_check_cred (struct ucred*,int /*<<< orphan*/ ) ; 
 int vaccess (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct ucred*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ksem_access(struct ksem *ks, struct ucred *ucred)
{
	int error;

	error = vaccess(VREG, ks->ks_mode, ks->ks_uid, ks->ks_gid,
	    VREAD | VWRITE, ucred, NULL);
	if (error)
		error = priv_check_cred(ucred, PRIV_SEM_WRITE);
	return (error);
}