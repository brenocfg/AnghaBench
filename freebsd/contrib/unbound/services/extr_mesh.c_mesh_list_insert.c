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
struct mesh_state {struct mesh_state* next; struct mesh_state* prev; } ;

/* Variables and functions */

void mesh_list_insert(struct mesh_state* m, struct mesh_state** fp,
        struct mesh_state** lp)
{
	/* insert as last element */
	m->prev = *lp;
	m->next = NULL;
	if(*lp)
		(*lp)->next = m;
	else	*fp = m;
	*lp = m;
}