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
 int /*<<< orphan*/  MAC_POLICY_PERFORM_NOSLEEP (int /*<<< orphan*/ ,struct ucred*,struct shmfd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  posixshm_create ; 

void
mac_posixshm_create(struct ucred *cred, struct shmfd *shmfd)
{

	MAC_POLICY_PERFORM_NOSLEEP(posixshm_create, cred, shmfd,
	    shmfd->shm_label);
}