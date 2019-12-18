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
struct thread {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYSVSHM_LOCK () ; 
 int /*<<< orphan*/  SYSVSHM_UNLOCK () ; 
 int kern_shmctl_locked (struct thread*,int,int,void*,size_t*) ; 

int
kern_shmctl(struct thread *td, int shmid, int cmd, void *buf, size_t *bufsz)
{
	int error;

	SYSVSHM_LOCK();
	error = kern_shmctl_locked(td, shmid, cmd, buf, bufsz);
	SYSVSHM_UNLOCK();
	return (error);
}