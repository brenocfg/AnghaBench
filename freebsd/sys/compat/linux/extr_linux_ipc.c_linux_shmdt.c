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
struct linux_shmdt_args {int /*<<< orphan*/  shmaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  PTRIN (int /*<<< orphan*/ ) ; 
 int sys_shmdt (struct thread*,struct shmdt_args*) ; 

int
linux_shmdt(struct thread *td, struct linux_shmdt_args *args)
{
	struct shmdt_args /* {
		void *shmaddr;
	} */ bsd_args;

	bsd_args.shmaddr = PTRIN(args->shmaddr);
	return (sys_shmdt(td, &bsd_args));
}