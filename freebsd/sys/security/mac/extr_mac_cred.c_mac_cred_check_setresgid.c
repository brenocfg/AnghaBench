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
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_CHECK_PROBE4 (int /*<<< orphan*/ ,int,struct ucred*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAC_POLICY_CHECK_NOSLEEP (int /*<<< orphan*/ ,struct ucred*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cred_check_setresgid ; 

int
mac_cred_check_setresgid(struct ucred *cred, gid_t rgid, gid_t egid,
    gid_t sgid)
{
	int error;

	MAC_POLICY_CHECK_NOSLEEP(cred_check_setresgid, cred, rgid, egid, sgid);
	MAC_CHECK_PROBE4(cred_check_setresgid, error, cred, rgid, egid,
	    sgid);

	return (error);
}