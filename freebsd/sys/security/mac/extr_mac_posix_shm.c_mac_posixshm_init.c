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
struct shmfd {int /*<<< orphan*/ * shm_label; } ;

/* Variables and functions */
 int MPC_OBJECT_POSIXSHM ; 
 int mac_labeled ; 
 int /*<<< orphan*/ * mac_posixshm_label_alloc () ; 

void
mac_posixshm_init(struct shmfd *shmfd)
{

	if (mac_labeled & MPC_OBJECT_POSIXSHM)
		shmfd->shm_label = mac_posixshm_label_alloc();
	else
		shmfd->shm_label = NULL;
}