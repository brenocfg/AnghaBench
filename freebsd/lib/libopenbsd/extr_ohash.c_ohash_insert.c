#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ohash {int total; int size; TYPE_1__* t; int /*<<< orphan*/  deleted; } ;
struct TYPE_2__ {void* p; } ;

/* Variables and functions */
 void* DELETED ; 
 int /*<<< orphan*/  STAT_HASH_ENTRIES ; 
 int /*<<< orphan*/  ohash_resize (struct ohash*) ; 

void *
ohash_insert(struct ohash *h, unsigned int i, void *p)
{
#ifdef STATS_HASH
	STAT_HASH_ENTRIES++;
#endif
	if (h->t[i].p == DELETED) {
		h->deleted--;
		h->t[i].p = p;
	} else {
		h->t[i].p = p;
		/* Arbitrary resize boundary.  Tweak if not efficient enough.  */
		if (++h->total * 4 > h->size * 3)
			ohash_resize(h);
	}
	return p;
}