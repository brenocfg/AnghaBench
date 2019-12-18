#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t namehash; struct TYPE_6__* next; } ;
struct TYPE_5__ {size_t mask; int /*<<< orphan*/  numEntries; TYPE_2__** bucketPtr; } ;
typedef  TYPE_1__ Hash_Table ;
typedef  TYPE_2__ Hash_Entry ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  write (int,char*,int) ; 

void
Hash_DeleteEntry(Hash_Table *t, Hash_Entry *e)
{
	register Hash_Entry **hp, *p;

	if (e == NULL)
		return;
	for (hp = &t->bucketPtr[e->namehash & t->mask];
	     (p = *hp) != NULL; hp = &p->next) {
		if (p == e) {
			*hp = p->next;
			free((char *)p);
			t->numEntries--;
			return;
		}
	}
	(void)write(2, "bad call to Hash_DeleteEntry\n", 29);
	abort();
}