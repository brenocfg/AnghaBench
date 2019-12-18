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
struct TYPE_4__ {int index; int /*<<< orphan*/ * tid; } ;
struct TYPE_5__ {TYPE_1__ tid_pool; } ;
typedef  TYPE_2__ pqisrc_softstate_t ;

/* Variables and functions */
 int PQI_MAX_LOGICALS ; 
 int PQI_MAX_PHYSICALS ; 

void  pqisrc_init_targetid_pool(pqisrc_softstate_t *softs)
{
	int i, tid = PQI_MAX_PHYSICALS + PQI_MAX_LOGICALS - 1;

	for(i = 0; i < PQI_MAX_PHYSICALS; i++) {
		softs->tid_pool.tid[i] = tid--;
	}
	softs->tid_pool.index = i - 1;
}