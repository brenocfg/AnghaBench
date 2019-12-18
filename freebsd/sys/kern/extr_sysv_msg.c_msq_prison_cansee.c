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
struct prison {int dummy; } ;
struct msqid_kernel {TYPE_1__* cred; } ;
struct TYPE_2__ {struct prison* cr_prison; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ prison_ischild (struct prison*,struct prison*) ; 

__attribute__((used)) static int
msq_prison_cansee(struct prison *rpr, struct msqid_kernel *msqkptr)
{

	if (msqkptr->cred == NULL ||
	    !(rpr == msqkptr->cred->cr_prison ||
	      prison_ischild(rpr, msqkptr->cred->cr_prison)))
		return (EINVAL);
	return (0);
}