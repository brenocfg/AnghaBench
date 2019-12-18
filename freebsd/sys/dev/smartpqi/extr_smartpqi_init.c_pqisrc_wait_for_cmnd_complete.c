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
struct TYPE_4__ {scalar_t__ num_elem; } ;
struct TYPE_5__ {scalar_t__ max_outstanding_io; TYPE_1__ taglist; } ;
typedef  TYPE_2__ pqisrc_softstate_t ;

/* Variables and functions */
 int /*<<< orphan*/  COND_WAIT (int,int) ; 
 int /*<<< orphan*/  DBG_ERR (char*,scalar_t__) ; 
 int PQI_CMND_COMPLETE_TMO ; 
 int PQI_STATUS_SUCCESS ; 
 int PQI_STATUS_TIMEOUT ; 

int pqisrc_wait_for_cmnd_complete(pqisrc_softstate_t *softs)
{
	int ret = PQI_STATUS_SUCCESS;
	int tmo = PQI_CMND_COMPLETE_TMO;
	
	COND_WAIT((softs->taglist.num_elem == softs->max_outstanding_io), tmo);
	if (!tmo) {
		DBG_ERR("Pending commands %x!!!",softs->taglist.num_elem);
		ret = PQI_STATUS_TIMEOUT;
	}
	return ret;
}