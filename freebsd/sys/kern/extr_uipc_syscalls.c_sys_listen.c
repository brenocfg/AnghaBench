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
struct listen_args {int /*<<< orphan*/  backlog; int /*<<< orphan*/  s; } ;

/* Variables and functions */
 int kern_listen (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
sys_listen(struct thread *td, struct listen_args *uap)
{

	return (kern_listen(td, uap->s, uap->backlog));
}