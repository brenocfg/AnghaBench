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
struct linux_sendmsg_args {int /*<<< orphan*/  flags; int /*<<< orphan*/  msg; int /*<<< orphan*/  s; } ;

/* Variables and functions */
 int /*<<< orphan*/  PTRIN (int /*<<< orphan*/ ) ; 
 int linux_sendmsg_common (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
linux_sendmsg(struct thread *td, struct linux_sendmsg_args *args)
{

	return (linux_sendmsg_common(td, args->s, PTRIN(args->msg),
	    args->flags));
}