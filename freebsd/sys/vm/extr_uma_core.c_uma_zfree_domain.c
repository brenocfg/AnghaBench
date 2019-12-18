#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zone ;
typedef  TYPE_1__* uma_zone_t ;
struct TYPE_8__ {scalar_t__ td_critnest; } ;
struct TYPE_7__ {int /*<<< orphan*/  uz_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTR2 (int /*<<< orphan*/ ,char*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  KTR_UMA ; 
 int /*<<< orphan*/  RANDOM_UMA ; 
 scalar_t__ SCHEDULER_STOPPED () ; 
 int /*<<< orphan*/  SKIP_NONE ; 
 TYPE_5__* curthread ; 
 int /*<<< orphan*/  random_harvest_fast_uma (TYPE_1__**,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zone_free_item (TYPE_1__*,void*,void*,int /*<<< orphan*/ ) ; 

void
uma_zfree_domain(uma_zone_t zone, void *item, void *udata)
{

	/* Enable entropy collection for RANDOM_ENABLE_UMA kernel option */
	random_harvest_fast_uma(&zone, sizeof(zone), RANDOM_UMA);

	CTR2(KTR_UMA, "uma_zfree_domain thread %x zone %s", curthread,
	    zone->uz_name);

	KASSERT(curthread->td_critnest == 0 || SCHEDULER_STOPPED(),
	    ("uma_zfree_domain: called with spinlock or critical section held"));

        /* uma_zfree(..., NULL) does nothing, to match free(9). */
        if (item == NULL)
                return;
	zone_free_item(zone, item, udata, SKIP_NONE);
}