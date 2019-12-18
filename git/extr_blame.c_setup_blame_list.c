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
struct blame_list {struct blame_entry* ent; } ;
struct blame_entry {struct blame_entry* next; } ;

/* Variables and functions */
 struct blame_list* xcalloc (int,int) ; 

__attribute__((used)) static struct blame_list *setup_blame_list(struct blame_entry *unblamed,
					   int *num_ents_p)
{
	struct blame_entry *e;
	int num_ents, i;
	struct blame_list *blame_list = NULL;

	for (e = unblamed, num_ents = 0; e; e = e->next)
		num_ents++;
	if (num_ents) {
		blame_list = xcalloc(num_ents, sizeof(struct blame_list));
		for (e = unblamed, i = 0; e; e = e->next)
			blame_list[i++].ent = e;
	}
	*num_ents_p = num_ents;
	return blame_list;
}