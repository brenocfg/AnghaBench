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
struct ohash {int deleted; int total; TYPE_1__* t; } ;
struct TYPE_2__ {void* p; } ;

/* Variables and functions */
 void* DELETED ; 
 int MINDELETED ; 
 int /*<<< orphan*/  STAT_HASH_ENTRIES ; 
 int /*<<< orphan*/  ohash_resize (struct ohash*) ; 

void *
ohash_remove(struct ohash *h, unsigned int i)
{
	void		*result = (void *)h->t[i].p;

	if (result == NULL || result == DELETED)
		return NULL;

#ifdef STATS_HASH
	STAT_HASH_ENTRIES--;
#endif
	h->t[i].p = DELETED;
	h->deleted++;
	if (h->deleted >= MINDELETED && 4 * h->deleted > h->total)
		ohash_resize(h);
	return result;
}