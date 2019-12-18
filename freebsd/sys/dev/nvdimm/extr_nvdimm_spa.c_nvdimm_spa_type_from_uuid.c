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
struct uuid {int dummy; } ;
typedef  enum SPA_mapping_type { ____Placeholder_SPA_mapping_type } SPA_mapping_type ;
struct TYPE_3__ {int /*<<< orphan*/  u_id; } ;

/* Variables and functions */
 int SPA_TYPE_UNKNOWN ; 
 int nitems (TYPE_1__*) ; 
 TYPE_1__* nvdimm_SPA_uuid_list ; 
 scalar_t__ uuidcmp (struct uuid*,int /*<<< orphan*/ *) ; 

enum SPA_mapping_type
nvdimm_spa_type_from_uuid(struct uuid *uuid)
{
	int j;

	for (j = 0; j < nitems(nvdimm_SPA_uuid_list); j++) {
		if (uuidcmp(uuid, &nvdimm_SPA_uuid_list[j].u_id) != 0)
			continue;
		return (j);
	}
	return (SPA_TYPE_UNKNOWN);
}