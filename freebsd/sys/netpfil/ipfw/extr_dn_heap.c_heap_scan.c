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
struct dn_heap {int elements; TYPE_1__* p; } ;
struct TYPE_2__ {void* object; } ;

/* Variables and functions */
 int HEAP_SCAN_DEL ; 
 int HEAP_SCAN_END ; 
 int /*<<< orphan*/  heapify (struct dn_heap*) ; 

int
heap_scan(struct dn_heap *h, int (*fn)(void *, uintptr_t),
	uintptr_t arg)
{
	int i, ret, found;

	for (i = found = 0 ; i < h->elements ;) {
		ret = fn(h->p[i].object, arg);
		if (ret & HEAP_SCAN_DEL) {
			h->elements-- ;
			h->p[i] = h->p[h->elements] ;
			found++ ;
		} else
			i++ ;
		if (ret & HEAP_SCAN_END)
			break;
	}
	if (found)
		heapify(h);
	return found;
}