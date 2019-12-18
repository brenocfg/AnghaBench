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
typedef  unsigned int uint32_t ;
struct cvmx_zone {int dummy; } ;
typedef  TYPE_2__* cvmx_zone_t ;
typedef  int /*<<< orphan*/  cvmx_arena_list_t ;
struct TYPE_4__ {int /*<<< orphan*/  value; } ;
struct TYPE_5__ {unsigned int elem_size; unsigned int num_elem; char* name; unsigned int align; char* baseptr; int /*<<< orphan*/ * freelist; TYPE_1__ lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_SPINLOCK_UNLOCKED_VAL ; 
 scalar_t__ cvmx_malloc (int /*<<< orphan*/ ,int) ; 
 scalar_t__ cvmx_memalign (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

cvmx_zone_t cvmx_zone_create_from_arena(char *name, uint32_t elem_size, uint32_t num_elem, uint32_t align, cvmx_arena_list_t arena_list, uint32_t flags)
{
    unsigned int i;
    cvmx_zone_t zone;

    zone = (cvmx_zone_t)cvmx_malloc(arena_list, sizeof(struct cvmx_zone));

    if (NULL == zone)
    {
        return(NULL);
    }
    zone->elem_size = elem_size;
    zone->num_elem = num_elem;
    zone->name = name;
    zone->align = align;
    zone->baseptr = NULL;
    zone->freelist = NULL;
    zone->lock.value = CVMX_SPINLOCK_UNLOCKED_VAL;

    zone->baseptr = (char *)cvmx_memalign(arena_list, align, num_elem * elem_size);
    if (NULL == zone->baseptr)
    {
        return(NULL);
    }

    for(i=0;i<num_elem;i++)
    {
        *(void **)(zone->baseptr + (i*elem_size)) = zone->freelist;
        zone->freelist = (void *)(zone->baseptr + (i*elem_size));
    }

    return(zone);

}