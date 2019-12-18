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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int /*<<< orphan*/  api_id; int /*<<< orphan*/  api_name_len; int /*<<< orphan*/  api_name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 scalar_t__ kstrtouint (char*,int,int /*<<< orphan*/ *) ; 
 TYPE_1__* pm_api_list ; 
 int /*<<< orphan*/  strncasecmp (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_pm_api_id(char *pm_api_req, u32 *pm_id)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(pm_api_list) ; i++) {
		if (!strncasecmp(pm_api_req, pm_api_list[i].api_name,
				 pm_api_list[i].api_name_len)) {
			*pm_id = pm_api_list[i].api_id;
			break;
		}
	}

	/* If no name was entered look for PM-API ID instead */
	if (i == ARRAY_SIZE(pm_api_list) && kstrtouint(pm_api_req, 10, pm_id))
		return -EINVAL;

	return 0;
}