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
struct busdma_bufzone {scalar_t__ size; } ;
typedef  TYPE_1__* busdma_bufalloc_t ;
typedef  scalar_t__ bus_size_t ;
struct TYPE_3__ {int num_zones; struct busdma_bufzone* buf_zones; } ;

/* Variables and functions */
 scalar_t__ MAX_ZONE_BUFSIZE ; 
 int /*<<< orphan*/  panic (char*) ; 

struct busdma_bufzone * 
busdma_bufalloc_findzone(busdma_bufalloc_t ba, bus_size_t size)
{
	struct busdma_bufzone *bz;
	int i;

	if (size > MAX_ZONE_BUFSIZE)
		return (NULL);

	for (i = 0, bz = ba->buf_zones; i < ba->num_zones; ++i, ++bz) {
		if (bz->size >= size)
			return (bz);
	}

	panic("Didn't find a buffer zone of the right size");
}