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
typedef  scalar_t__ u_short ;
struct TYPE_4__ {scalar_t__ bfc_bsm_fcntl_cmd; } ;
typedef  TYPE_1__ bsm_fcntl_cmd_t ;

/* Variables and functions */
 int bsm_fcntl_cmd_count ; 
 TYPE_1__ const* bsm_fcntl_cmdtab ; 

__attribute__((used)) static const bsm_fcntl_cmd_t *
bsm_lookup_bsm_fcntl_cmd(u_short bsm_fcntl_cmd)
{
	int i;

	for (i = 0; i < bsm_fcntl_cmd_count; i++) {
		if (bsm_fcntl_cmdtab[i].bfc_bsm_fcntl_cmd ==
		    bsm_fcntl_cmd)
			return (&bsm_fcntl_cmdtab[i]);
	}
	return (NULL);
}