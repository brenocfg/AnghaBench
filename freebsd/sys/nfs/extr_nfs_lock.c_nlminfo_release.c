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
struct proc {int /*<<< orphan*/ * p_nlminfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_NLMINFO ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void        
nlminfo_release(struct proc *p)
{  
	free(p->p_nlminfo, M_NLMINFO);
	p->p_nlminfo = NULL;
}