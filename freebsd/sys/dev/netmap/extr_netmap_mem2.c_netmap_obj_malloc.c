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
typedef  size_t uint32_t ;
typedef  scalar_t__ u_int ;
struct netmap_obj_pool {scalar_t__ _objsize; scalar_t__ objfree; size_t bitmap_slots; size_t* bitmap; int /*<<< orphan*/  name; TYPE_1__* lut; } ;
struct TYPE_2__ {void* vaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  nm_prdis (char*,int /*<<< orphan*/ ,size_t,size_t,void*) ; 
 int /*<<< orphan*/  nm_prerr (char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void *
netmap_obj_malloc(struct netmap_obj_pool *p, u_int len, uint32_t *start, uint32_t *index)
{
	uint32_t i = 0;			/* index in the bitmap */
	uint32_t mask, j = 0;		/* slot counter */
	void *vaddr = NULL;

	if (len > p->_objsize) {
		nm_prerr("%s request size %d too large", p->name, len);
		return NULL;
	}

	if (p->objfree == 0) {
		nm_prerr("no more %s objects", p->name);
		return NULL;
	}
	if (start)
		i = *start;

	/* termination is guaranteed by p->free, but better check bounds on i */
	while (vaddr == NULL && i < p->bitmap_slots)  {
		uint32_t cur = p->bitmap[i];
		if (cur == 0) { /* bitmask is fully used */
			i++;
			continue;
		}
		/* locate a slot */
		for (j = 0, mask = 1; (cur & mask) == 0; j++, mask <<= 1)
			;

		p->bitmap[i] &= ~mask; /* mark object as in use */
		p->objfree--;

		vaddr = p->lut[i * 32 + j].vaddr;
		if (index)
			*index = i * 32 + j;
	}
	nm_prdis("%s allocator: allocated object @ [%d][%d]: vaddr %p",p->name, i, j, vaddr);

	if (start)
		*start = i;
	return vaddr;
}