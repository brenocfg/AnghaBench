#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char const* name; } ;
struct entry {TYPE_2__ sym; struct entry* link; } ;
typedef  TYPE_1__* Table ;
struct TYPE_6__ {struct entry** buckets; struct TYPE_6__* previous; } ;
typedef  TYPE_2__* Symbol ;

/* Variables and functions */
 int HASHSIZE ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 

Symbol lookup(const char *name, Table tp) {
	struct entry *p;
	unsigned h = (unsigned long)name&(HASHSIZE-1);

	assert(tp);
	do
		for (p = tp->buckets[h]; p; p = p->link)
			if (name == p->sym.name)
				return &p->sym;
	while ((tp = tp->previous) != NULL);
	return NULL;
}