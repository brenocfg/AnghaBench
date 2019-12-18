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

/* Variables and functions */
 int /*<<< orphan*/  MAC_CHECK_PROBE3 (int /*<<< orphan*/ ,int,struct ucred*,void*,int) ; 
 int /*<<< orphan*/  MAC_POLICY_CHECK_NOSLEEP (int /*<<< orphan*/ ,struct ucred*,void*,int) ; 
 int /*<<< orphan*/  system_check_audit ; 

int
mac_system_check_audit(struct ucred *cred, void *record, int length)
{
	int error;

	MAC_POLICY_CHECK_NOSLEEP(system_check_audit, cred, record, length);
	MAC_CHECK_PROBE3(system_check_audit, error, cred, record, length);

	return (error);
}