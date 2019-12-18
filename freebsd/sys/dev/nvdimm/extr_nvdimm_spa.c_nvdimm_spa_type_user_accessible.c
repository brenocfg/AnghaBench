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
typedef  enum SPA_mapping_type { ____Placeholder_SPA_mapping_type } SPA_mapping_type ;
struct TYPE_3__ {int u_usr_acc; } ;

/* Variables and functions */
 int nitems (TYPE_1__*) ; 
 TYPE_1__* nvdimm_SPA_uuid_list ; 

bool
nvdimm_spa_type_user_accessible(enum SPA_mapping_type spa_type)
{

	if ((int)spa_type < 0 || spa_type >= nitems(nvdimm_SPA_uuid_list))
		return (false);
	return (nvdimm_SPA_uuid_list[spa_type].u_usr_acc);
}