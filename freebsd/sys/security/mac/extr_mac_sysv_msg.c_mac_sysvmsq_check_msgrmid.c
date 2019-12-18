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
struct msg {int /*<<< orphan*/  label; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_CHECK_PROBE2 (int /*<<< orphan*/ ,int,struct ucred*,struct msg*) ; 
 int /*<<< orphan*/  MAC_POLICY_CHECK_NOSLEEP (int /*<<< orphan*/ ,struct ucred*,struct msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysvmsq_check_msgrmid ; 

int
mac_sysvmsq_check_msgrmid(struct ucred *cred, struct msg *msgptr)
{
	int error;

	MAC_POLICY_CHECK_NOSLEEP(sysvmsq_check_msgrmid, cred, msgptr,
	    msgptr->label);
	MAC_CHECK_PROBE2(sysvmsq_check_msgrmid, error, cred, msgptr);

	return (error);
}