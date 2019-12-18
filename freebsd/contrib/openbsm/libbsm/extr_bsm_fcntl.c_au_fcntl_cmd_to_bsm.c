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
typedef  int /*<<< orphan*/  u_short ;
struct TYPE_3__ {int /*<<< orphan*/  bfc_bsm_fcntl_cmd; } ;
typedef  TYPE_1__ bsm_fcntl_cmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  BSM_F_UNKNOWN ; 
 TYPE_1__* bsm_lookup_local_fcntl_cmd (int) ; 

u_short
au_fcntl_cmd_to_bsm(int local_fcntl_cmd)
{
	const bsm_fcntl_cmd_t *bfcp;

	bfcp = bsm_lookup_local_fcntl_cmd(local_fcntl_cmd);
	if (bfcp == NULL)
		return (BSM_F_UNKNOWN);
	return (bfcp->bfc_bsm_fcntl_cmd);
}