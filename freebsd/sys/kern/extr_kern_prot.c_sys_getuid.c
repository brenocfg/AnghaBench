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
struct getuid_args {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  cr_uid; int /*<<< orphan*/  cr_ruid; } ;

/* Variables and functions */

int
sys_getuid(struct thread *td, struct getuid_args *uap)
{

	td->td_retval[0] = td->td_ucred->cr_ruid;
#if defined(COMPAT_43)
	td->td_retval[1] = td->td_ucred->cr_uid;
#endif
	return (0);
}