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
typedef  int /*<<< orphan*/  uid_t ;
struct ucred {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_CHECK_PROBE3 (int /*<<< orphan*/ ,int,struct ucred*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAC_POLICY_CHECK_NOSLEEP (int /*<<< orphan*/ ,struct ucred*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cred_check_setreuid ; 

int
mac_cred_check_setreuid(struct ucred *cred, uid_t ruid, uid_t euid)
{
	int error;

	MAC_POLICY_CHECK_NOSLEEP(cred_check_setreuid, cred, ruid, euid);
	MAC_CHECK_PROBE3(cred_check_setreuid, error, cred, ruid, euid);

	return (error);
}