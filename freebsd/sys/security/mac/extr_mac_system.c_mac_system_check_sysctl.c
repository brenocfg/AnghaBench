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
struct sysctl_req {int dummy; } ;
struct sysctl_oid {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_CHECK_PROBE3 (int /*<<< orphan*/ ,int,struct ucred*,struct sysctl_oid*,struct sysctl_req*) ; 
 int /*<<< orphan*/  MAC_POLICY_CHECK_NOSLEEP (int /*<<< orphan*/ ,struct ucred*,struct sysctl_oid*,void*,int,struct sysctl_req*) ; 
 int /*<<< orphan*/  system_check_sysctl ; 

int
mac_system_check_sysctl(struct ucred *cred, struct sysctl_oid *oidp,
    void *arg1, int arg2, struct sysctl_req *req)
{
	int error;

	/*
	 * XXXMAC: We would very much like to assert the SYSCTL_LOCK here,
	 * but since it's not exported from kern_sysctl.c, we can't.
	 */
	MAC_POLICY_CHECK_NOSLEEP(system_check_sysctl, cred, oidp, arg1, arg2,
	    req);
	MAC_CHECK_PROBE3(system_check_sysctl, error, cred, oidp, req);

	return (error);
}