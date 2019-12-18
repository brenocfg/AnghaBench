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
struct shmdt_args {int /*<<< orphan*/  shmaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYSVSHM_LOCK () ; 
 int /*<<< orphan*/  SYSVSHM_UNLOCK () ; 
 int kern_shmdt_locked (struct thread*,int /*<<< orphan*/ ) ; 

int
sys_shmdt(struct thread *td, struct shmdt_args *uap)
{
	int error;

	SYSVSHM_LOCK();
	error = kern_shmdt_locked(td, uap->shmaddr);
	SYSVSHM_UNLOCK();
	return (error);
}