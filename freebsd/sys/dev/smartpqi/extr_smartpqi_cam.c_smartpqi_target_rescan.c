#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pqisrc_softstate {scalar_t__** device_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_FUNC (char*) ; 
 int PQI_MAX_DEVICES ; 
 int PQI_MAX_MULTILUN ; 
 int /*<<< orphan*/  smartpqi_lun_rescan (struct pqisrc_softstate*,int,int) ; 

void smartpqi_target_rescan(struct pqisrc_softstate *softs)
{
	int target = 0, lun = 0;

	DBG_FUNC("IN\n");

	for(target = 0; target < PQI_MAX_DEVICES; target++){
		for(lun = 0; lun < PQI_MAX_MULTILUN; lun++){
			if(softs->device_list[target][lun]){
				smartpqi_lun_rescan(softs, target, lun);
			}
		}
	}

	DBG_FUNC("OUT\n");
}