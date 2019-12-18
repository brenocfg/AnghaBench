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
struct thread {TYPE_1__* td_ucred; } ;
struct prison {int /*<<< orphan*/  pr_mtx; } ;
struct linux_prison {int /*<<< orphan*/  pr_osname; } ;
struct TYPE_2__ {int /*<<< orphan*/  cr_prison; } ;

/* Variables and functions */
 int /*<<< orphan*/  LINUX_MAX_UTSNAME ; 
 struct linux_prison* linux_find_prison (int /*<<< orphan*/ ,struct prison**) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
linux_set_osname(struct thread *td, char *osname)
{
	struct prison *pr;
	struct linux_prison *lpr;

	lpr = linux_find_prison(td->td_ucred->cr_prison, &pr);
	strlcpy(lpr->pr_osname, osname, LINUX_MAX_UTSNAME);
	mtx_unlock(&pr->pr_mtx);

	return (0);
}