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
struct linux_listen_args {int /*<<< orphan*/  backlog; int /*<<< orphan*/  s; } ;

/* Variables and functions */
 int kern_listen (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
linux_listen(struct thread *td, struct linux_listen_args *args)
{

	return (kern_listen(td, args->s, args->backlog));
}