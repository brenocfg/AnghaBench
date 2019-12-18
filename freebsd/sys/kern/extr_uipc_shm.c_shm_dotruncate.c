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
struct shmfd {int /*<<< orphan*/  shm_mtx; int /*<<< orphan*/  shm_rl; int /*<<< orphan*/  shm_object; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int /*<<< orphan*/  OFF_MAX ; 
 int /*<<< orphan*/  VM_OBJECT_WLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_OBJECT_WUNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rangelock_unlock (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *) ; 
 void* rangelock_wlock (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int shm_dotruncate_locked (struct shmfd*,int /*<<< orphan*/ ,void*) ; 

int
shm_dotruncate(struct shmfd *shmfd, off_t length)
{
	void *rl_cookie;
	int error;

	rl_cookie = rangelock_wlock(&shmfd->shm_rl, 0, OFF_MAX,
	    &shmfd->shm_mtx);
	VM_OBJECT_WLOCK(shmfd->shm_object);
	error = shm_dotruncate_locked(shmfd, length, rl_cookie);
	VM_OBJECT_WUNLOCK(shmfd->shm_object);
	rangelock_unlock(&shmfd->shm_rl, rl_cookie, &shmfd->shm_mtx);
	return (error);
}