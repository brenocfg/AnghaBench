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
struct auditinfo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_CHECK_PROBE2 (int /*<<< orphan*/ ,int,struct ucred*,struct auditinfo*) ; 
 int /*<<< orphan*/  MAC_POLICY_CHECK_NOSLEEP (int /*<<< orphan*/ ,struct ucred*,struct auditinfo*) ; 
 int /*<<< orphan*/  cred_check_setaudit ; 

int
mac_cred_check_setaudit(struct ucred *cred, struct auditinfo *ai)
{
	int error;

	MAC_POLICY_CHECK_NOSLEEP(cred_check_setaudit, cred, ai);
	MAC_CHECK_PROBE2(cred_check_setaudit, error, cred, ai);

	return (error);
}