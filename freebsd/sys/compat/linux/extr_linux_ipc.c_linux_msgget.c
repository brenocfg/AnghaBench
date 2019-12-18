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
struct msgget_args {int /*<<< orphan*/  msgflg; int /*<<< orphan*/  key; } ;
struct linux_msgget_args {int /*<<< orphan*/  msgflg; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int sys_msgget (struct thread*,struct msgget_args*) ; 

int
linux_msgget(struct thread *td, struct linux_msgget_args *args)
{
	struct msgget_args /* {
		key_t	key;
		int	msgflg;
	} */ bsd_args;

	bsd_args.key = args->key;
	bsd_args.msgflg = args->msgflg;
	return (sys_msgget(td, &bsd_args));
}