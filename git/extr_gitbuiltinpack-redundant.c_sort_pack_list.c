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
struct pack_list {struct pack_list* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  QSORT (struct pack_list**,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmp_remaining_objects ; 
 int /*<<< orphan*/  free (struct pack_list**) ; 
 size_t pack_list_size (struct pack_list*) ; 
 struct pack_list** xcalloc (size_t,int) ; 

__attribute__((used)) static void sort_pack_list(struct pack_list **pl)
{
	struct pack_list **ary, *p;
	int i;
	size_t n = pack_list_size(*pl);

	if (n < 2)
		return;

	/* prepare an array of packed_list for easier sorting */
	ary = xcalloc(n, sizeof(struct pack_list *));
	for (n = 0, p = *pl; p; p = p->next)
		ary[n++] = p;

	QSORT(ary, n, cmp_remaining_objects);

	/* link them back again */
	for (i = 0; i < n - 1; i++)
		ary[i]->next = ary[i + 1];
	ary[n - 1]->next = NULL;
	*pl = ary[0];

	free(ary);
}