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
struct ucred {scalar_t__ cr_prison; } ;

/* Variables and functions */
 int ESRCH ; 
 scalar_t__ prison_ischild (scalar_t__,scalar_t__) ; 

int
prison_check(struct ucred *cred1, struct ucred *cred2)
{

	return ((cred1->cr_prison == cred2->cr_prison ||
	    prison_ischild(cred1->cr_prison, cred2->cr_prison)) ? 0 : ESRCH);
}