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
struct shmid_kernel {int /*<<< orphan*/  label; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_CHECK_PROBE3 (int /*<<< orphan*/ ,int,struct ucred*,struct shmid_kernel*,int) ; 
 int /*<<< orphan*/  MAC_POLICY_CHECK_NOSLEEP (int /*<<< orphan*/ ,struct ucred*,struct shmid_kernel*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sysvshm_check_shmctl ; 

int
mac_sysvshm_check_shmctl(struct ucred *cred, struct shmid_kernel *shmsegptr,
    int cmd)
{
	int error;

	MAC_POLICY_CHECK_NOSLEEP(sysvshm_check_shmctl, cred, shmsegptr,
	    shmsegptr->label, cmd);
	MAC_CHECK_PROBE3(sysvshm_check_shmctl, error, cred, shmsegptr, cmd);

	return (error);
}