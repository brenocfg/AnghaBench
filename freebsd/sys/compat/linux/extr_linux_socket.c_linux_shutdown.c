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
struct linux_shutdown_args {int /*<<< orphan*/  how; int /*<<< orphan*/  s; } ;

/* Variables and functions */
 int kern_shutdown (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
linux_shutdown(struct thread *td, struct linux_shutdown_args *args)
{

	return (kern_shutdown(td, args->s, args->how));
}