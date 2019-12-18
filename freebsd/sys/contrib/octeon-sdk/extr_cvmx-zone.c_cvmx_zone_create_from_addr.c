#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int uint32_t ;
struct cvmx_zone {int dummy; } ;
typedef  TYPE_2__* cvmx_zone_t ;
struct TYPE_4__ {int /*<<< orphan*/  value; } ;
struct TYPE_5__ {int elem_size; int num_elem; char* name; char* baseptr; int /*<<< orphan*/ * freelist; TYPE_1__ lock; scalar_t__ align; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_SPINLOCK_UNLOCKED_VAL ; 

cvmx_zone_t cvmx_zone_create_from_addr(char *name, uint32_t elem_size, uint32_t num_elem,
                             void* mem_ptr, uint64_t mem_size, uint32_t flags)
{
    cvmx_zone_t zone;
    unsigned int i;

    if ((unsigned long)mem_ptr & (sizeof(void *) -1))
    {
        return(NULL);  //invalid alignment
    }
    if (mem_size  < sizeof(struct cvmx_zone) + elem_size * num_elem)
    {
        return(NULL);  // not enough room
    }

    zone = (cvmx_zone_t) ((char *)mem_ptr + elem_size * num_elem);
    zone->elem_size = elem_size;
    zone->num_elem = num_elem;
    zone->name = name;
    zone->align = 0;  // not used
    zone->baseptr = NULL;
    zone->freelist = NULL;
    zone->lock.value = CVMX_SPINLOCK_UNLOCKED_VAL;

    zone->baseptr = (char *)mem_ptr;

    for(i=0;i<num_elem;i++)
    {
        *(void **)(zone->baseptr + (i*elem_size)) = zone->freelist;
        zone->freelist = (void *)(zone->baseptr + (i*elem_size));
    }

    return(zone);

}