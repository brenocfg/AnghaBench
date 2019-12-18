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
struct ksem {int /*<<< orphan*/  ks_label; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_CHECK_PROBE3 (int /*<<< orphan*/ ,int,struct ucred*,struct ucred*,struct ksem*) ; 
 int /*<<< orphan*/  MAC_POLICY_CHECK_NOSLEEP (int /*<<< orphan*/ ,struct ucred*,struct ucred*,struct ksem*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  posixsem_check_wait ; 

int
mac_posixsem_check_wait(struct ucred *active_cred, struct ucred *file_cred,
    struct ksem *ks)
{
	int error;

	MAC_POLICY_CHECK_NOSLEEP(posixsem_check_wait, active_cred, file_cred,
	    ks, ks->ks_label);
	MAC_CHECK_PROBE3(posixsem_check_wait, error, active_cred, file_cred,
	    ks);

	return (error);
}