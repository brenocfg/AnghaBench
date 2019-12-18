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
struct valuelist {struct valuelist* proto; struct valuelist* name; struct valuelist* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct valuelist*) ; 
 struct valuelist* servicelist ; 

void
res_destroyservicelist() {
	struct valuelist *slp, *slp_next;

	for (slp = servicelist; slp != NULL; slp = slp_next) {
		slp_next = slp->next;
		free(slp->name);
		free(slp->proto);
		free(slp);
	}
	servicelist = (struct valuelist *)0;
}