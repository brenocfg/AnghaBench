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
struct ucred {TYPE_1__* cr_prison; } ;
struct TYPE_2__ {int pr_allow; } ;

/* Variables and functions */
 int EPERM ; 
 scalar_t__ jailed (struct ucred*) ; 
 int pr_allow_flag ; 

__attribute__((used)) static int
vmm_priv_check(struct ucred *ucred)
{

	if (jailed(ucred) &&
	    !(ucred->cr_prison->pr_allow & pr_allow_flag))
		return (EPERM);

	return (0);
}