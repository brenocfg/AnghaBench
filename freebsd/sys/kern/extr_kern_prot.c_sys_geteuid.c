#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct thread {TYPE_1__* td_ucred; int /*<<< orphan*/ * td_retval; } ;
struct geteuid_args {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  cr_uid; } ;

/* Variables and functions */

int
sys_geteuid(struct thread *td, struct geteuid_args *uap)
{

	td->td_retval[0] = td->td_ucred->cr_uid;
	return (0);
}