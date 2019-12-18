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
struct shmfd {int /*<<< orphan*/  shm_label; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_CHECK_PROBE2 (int /*<<< orphan*/ ,int,struct ucred*,struct shmfd*) ; 
 int /*<<< orphan*/  MAC_POLICY_CHECK_NOSLEEP (int /*<<< orphan*/ ,struct ucred*,struct shmfd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  posixshm_check_unlink ; 

int
mac_posixshm_check_unlink(struct ucred *cred, struct shmfd *shmfd)
{
	int error;

	MAC_POLICY_CHECK_NOSLEEP(posixshm_check_unlink, cred, shmfd,
	    shmfd->shm_label);
	MAC_CHECK_PROBE2(posixshm_check_unlink, error, cred, shmfd);

	return (error);
}