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
struct shmat_args {int /*<<< orphan*/  shmflg; int /*<<< orphan*/  shmaddr; int /*<<< orphan*/  shmid; } ;
struct linux_shmat_args {int /*<<< orphan*/  shmflg; int /*<<< orphan*/  shmaddr; int /*<<< orphan*/  shmid; } ;

/* Variables and functions */
 int /*<<< orphan*/  PTRIN (int /*<<< orphan*/ ) ; 
 int sys_shmat (struct thread*,struct shmat_args*) ; 

int
linux_shmat(struct thread *td, struct linux_shmat_args *args)
{
	struct shmat_args /* {
		int shmid;
		void *shmaddr;
		int shmflg;
	} */ bsd_args;

	bsd_args.shmid = args->shmid;
	bsd_args.shmaddr = PTRIN(args->shmaddr);
	bsd_args.shmflg = args->shmflg;
	return (sys_shmat(td, &bsd_args));
}