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
struct process {int dummy; } ;

/* Variables and functions */
 struct process* pcurrent ; 
 struct process* pgetcurr (struct process*) ; 
 struct process* pprevious ; 

__attribute__((used)) static void
pclrcurr(struct process *pp)
{
    if (pp == pcurrent) {
	if (pprevious != NULL) {
	    pcurrent = pprevious;
	    pprevious = pgetcurr(pp);
	}
	else {
	    pcurrent = pgetcurr(pp);
	    pprevious = pgetcurr(pp);
	}
    }
    else if (pp == pprevious)
	pprevious = pgetcurr(pp);
}