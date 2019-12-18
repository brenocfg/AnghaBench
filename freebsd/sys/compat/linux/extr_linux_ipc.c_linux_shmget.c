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
struct shmget_args {int /*<<< orphan*/  shmflg; int /*<<< orphan*/  size; int /*<<< orphan*/  key; } ;
struct linux_shmget_args {int /*<<< orphan*/  shmflg; int /*<<< orphan*/  size; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int sys_shmget (struct thread*,struct shmget_args*) ; 

int
linux_shmget(struct thread *td, struct linux_shmget_args *args)
{
	struct shmget_args /* {
		key_t key;
		int size;
		int shmflg;
	} */ bsd_args;

	bsd_args.key = args->key;
	bsd_args.size = args->size;
	bsd_args.shmflg = args->shmflg;
	return (sys_shmget(td, &bsd_args));
}