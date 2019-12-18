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
struct listen_list {int /*<<< orphan*/  com; struct listen_list* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  comm_point_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct listen_list*) ; 

void
listen_list_delete(struct listen_list* list)
{
	struct listen_list *p = list, *pn;
	while(p) {
		pn = p->next;
		comm_point_delete(p->com);
		free(p);
		p = pn;
	}
}