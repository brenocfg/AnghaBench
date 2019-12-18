#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int n_narcs; int n_arcsize; int /*<<< orphan*/  n_refcnt; struct TYPE_5__** n_arcs; } ;
typedef  TYPE_1__ NODE ;

/* Variables and functions */
 TYPE_1__* get_node (char*) ; 
 TYPE_1__** grow_buf (TYPE_1__**,int) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static void
add_arc(char *s1, char *s2)
{
	NODE *n1;
	NODE *n2;
	int bsize, i;

	n1 = get_node(s1);

	if (!strcmp(s1, s2))
		return;

	n2 = get_node(s2);

	/*
	 * Check if this arc is already here.
	 */
	for (i = 0; i < n1->n_narcs; i++)
		if (n1->n_arcs[i] == n2)
			return;
	/*
	 * Add it.
	 */
	if (n1->n_narcs == n1->n_arcsize) {
		if (!n1->n_arcsize)
			n1->n_arcsize = 10;
		bsize = n1->n_arcsize * sizeof(*n1->n_arcs) * 2;
		n1->n_arcs = grow_buf(n1->n_arcs, bsize);
		n1->n_arcsize = bsize / sizeof(*n1->n_arcs);
	}
	n1->n_arcs[n1->n_narcs++] = n2;
	++n2->n_refcnt;
}