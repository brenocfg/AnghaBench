#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* td_ucred; } ;
struct TYPE_5__ {TYPE_1__* cr_prison; } ;
struct TYPE_4__ {char* pr_hostname; } ;

/* Variables and functions */
 TYPE_3__* curthread ; 
 scalar_t__ jailed (TYPE_2__*) ; 

__attribute__((used)) static char *
spa_history_zone(void)
{
#ifdef _KERNEL
	/* XXX: pr_hostname can be changed by default from within a jail! */
	if (jailed(curthread->td_ucred))
		return (curthread->td_ucred->cr_prison->pr_hostname);
#endif
	return (NULL);
}