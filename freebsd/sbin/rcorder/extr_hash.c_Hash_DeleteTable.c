#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct Hash_Entry {struct Hash_Entry* next; } ;
struct TYPE_3__ {int size; struct Hash_Entry** bucketPtr; } ;
typedef  TYPE_1__ Hash_Table ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 

void
Hash_DeleteTable(Hash_Table *t)
{
	register struct Hash_Entry **hp, *h, *nexth = NULL;
	register int i;

	for (hp = t->bucketPtr, i = t->size; --i >= 0;) {
		for (h = *hp++; h != NULL; h = nexth) {
			nexth = h->next;
			free((char *)h);
		}
	}
	free((char *)t->bucketPtr);

	/*
	 * Set up the hash table to cause memory faults on any future access
	 * attempts until re-initialization.
	 */
	t->bucketPtr = NULL;
}