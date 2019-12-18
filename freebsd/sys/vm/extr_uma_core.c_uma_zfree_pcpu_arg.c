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
struct TYPE_4__ {int uz_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPASS (int) ; 
 int UMA_ZONE_PCPU ; 
 int /*<<< orphan*/  uma_zfree_arg (TYPE_1__*,void*,void*) ; 

void
uma_zfree_pcpu_arg(uma_zone_t zone, void *item, void *udata)
{

#ifdef SMP
	MPASS(zone->uz_flags & UMA_ZONE_PCPU);
#endif
	uma_zfree_arg(zone, item, udata);
}