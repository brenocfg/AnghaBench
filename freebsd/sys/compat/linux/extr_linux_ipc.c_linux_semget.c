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
struct semget_args {scalar_t__ nsems; int /*<<< orphan*/  semflg; int /*<<< orphan*/  key; } ;
struct linux_semget_args {scalar_t__ nsems; int /*<<< orphan*/  semflg; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int EINVAL ; 
 int sys_semget (struct thread*,struct semget_args*) ; 

int
linux_semget(struct thread *td, struct linux_semget_args *args)
{
	struct semget_args /* {
	key_t	key;
	int		nsems;
	int		semflg;
	} */ bsd_args;

	if (args->nsems < 0)
		return (EINVAL);
	bsd_args.key = args->key;
	bsd_args.nsems = args->nsems;
	bsd_args.semflg = args->semflg;
	return (sys_semget(td, &bsd_args));
}