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
struct prison {int pr_flags; struct prison* pr_parent; } ;

/* Variables and functions */
 int PR_IP4_USER ; 
 int PR_VNET ; 
 struct prison prison0 ; 

int
prison_equal_ip4(struct prison *pr1, struct prison *pr2)
{

	if (pr1 == pr2)
		return (1);

	/*
	 * No need to lock since the PR_IP4_USER flag can't be altered for
	 * existing prisons.
	 */
	while (pr1 != &prison0 &&
#ifdef VIMAGE
	       !(pr1->pr_flags & PR_VNET) &&
#endif
	       !(pr1->pr_flags & PR_IP4_USER))
		pr1 = pr1->pr_parent;
	while (pr2 != &prison0 &&
#ifdef VIMAGE
	       !(pr2->pr_flags & PR_VNET) &&
#endif
	       !(pr2->pr_flags & PR_IP4_USER))
		pr2 = pr2->pr_parent;
	return (pr1 == pr2);
}