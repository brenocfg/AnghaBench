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
 int /*<<< orphan*/  MAC_CHECK_PROBE2 (int /*<<< orphan*/ ,int,struct ucred*,struct ucred*) ; 
 int /*<<< orphan*/  MAC_POLICY_CHECK_NOSLEEP (int /*<<< orphan*/ ,struct ucred*,struct ucred*) ; 
 int /*<<< orphan*/  cred_check_visible ; 

int
mac_cred_check_visible(struct ucred *cr1, struct ucred *cr2)
{
	int error;

	MAC_POLICY_CHECK_NOSLEEP(cred_check_visible, cr1, cr2);
	MAC_CHECK_PROBE2(cred_check_visible, error, cr1, cr2);

	return (error);
}