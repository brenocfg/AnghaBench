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
struct TYPE_4__ {int bfc_local_fcntl_cmd; } ;
typedef  TYPE_1__ bsm_fcntl_cmd_t ;

/* Variables and functions */
 int bsm_fcntl_cmd_count ; 
 TYPE_1__ const* bsm_fcntl_cmdtab ; 

__attribute__((used)) static const bsm_fcntl_cmd_t *
bsm_lookup_local_fcntl_cmd(int local_fcntl_cmd)
{
	int i;

	for (i = 0; i < bsm_fcntl_cmd_count; i++) {
		if (bsm_fcntl_cmdtab[i].bfc_local_fcntl_cmd ==
		    local_fcntl_cmd)
			return (&bsm_fcntl_cmdtab[i]);
	}
	return (NULL);
}