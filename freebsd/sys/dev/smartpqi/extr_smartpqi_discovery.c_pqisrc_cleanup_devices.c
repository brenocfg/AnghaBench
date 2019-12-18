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
struct TYPE_4__ {int /*<<< orphan*/ *** device_list; } ;
typedef  TYPE_1__ pqisrc_softstate_t ;
typedef  int /*<<< orphan*/  pqi_scsi_dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_FUNC (char*) ; 
 int PQI_MAX_DEVICES ; 
 int PQI_MAX_MULTILUN ; 
 int /*<<< orphan*/  pqisrc_device_mem_free (TYPE_1__*,int /*<<< orphan*/ *) ; 

void pqisrc_cleanup_devices(pqisrc_softstate_t *softs)
{

	int i = 0,j = 0;
	pqi_scsi_dev_t *dvp = NULL;
	DBG_FUNC("IN\n");
	
 	for(i = 0; i < PQI_MAX_DEVICES; i++) {
		for(j = 0; j < PQI_MAX_MULTILUN; j++) {
			if (softs->device_list[i][j] == NULL) 
				continue;
			dvp = softs->device_list[i][j];
			pqisrc_device_mem_free(softs, dvp);
		}
	}
	DBG_FUNC("OUT\n");
}