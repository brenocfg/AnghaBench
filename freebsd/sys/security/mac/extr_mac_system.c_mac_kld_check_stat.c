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
 int /*<<< orphan*/  MAC_CHECK_PROBE1 (int /*<<< orphan*/ ,int,struct ucred*) ; 
 int /*<<< orphan*/  MAC_POLICY_CHECK_NOSLEEP (int /*<<< orphan*/ ,struct ucred*) ; 
 int /*<<< orphan*/  kld_check_stat ; 

int
mac_kld_check_stat(struct ucred *cred)
{
	int error;

	MAC_POLICY_CHECK_NOSLEEP(kld_check_stat, cred);
	MAC_CHECK_PROBE1(kld_check_stat, error, cred);

	return (error);
}