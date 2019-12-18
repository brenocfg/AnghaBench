#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* uma_zone_t ;
struct TYPE_4__ {int uz_flags; int /*<<< orphan*/  uz_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPASS (int) ; 
 int M_ZERO ; 
 int UMA_ZONE_PCPU ; 
 int /*<<< orphan*/  bzero (void*,int /*<<< orphan*/ ) ; 
 int mp_maxid ; 
 void* uma_zalloc_arg (TYPE_1__*,void*,int) ; 
 void* zpcpu_get_cpu (void*,int) ; 

void *
uma_zalloc_pcpu_arg(uma_zone_t zone, void *udata, int flags)
{
	void *item;
#ifdef SMP
	int i;

	MPASS(zone->uz_flags & UMA_ZONE_PCPU);
#endif
	item = uma_zalloc_arg(zone, udata, flags & ~M_ZERO);
	if (item != NULL && (flags & M_ZERO)) {
#ifdef SMP
		for (i = 0; i <= mp_maxid; i++)
			bzero(zpcpu_get_cpu(item, i), zone->uz_size);
#else
		bzero(item, zone->uz_size);
#endif
	}
	return (item);
}