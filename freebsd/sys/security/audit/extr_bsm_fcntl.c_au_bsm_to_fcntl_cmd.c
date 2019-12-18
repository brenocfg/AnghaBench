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
struct TYPE_3__ {int bfc_local_fcntl_cmd; } ;
typedef  TYPE_1__ bsm_fcntl_cmd_t ;

/* Variables and functions */
 TYPE_1__* bsm_lookup_bsm_fcntl_cmd (int /*<<< orphan*/ ) ; 

int
au_bsm_to_fcntl_cmd(u_short bsm_fcntl_cmd, int *local_fcntl_cmdp)
{
	const bsm_fcntl_cmd_t *bfcp;

	bfcp = bsm_lookup_bsm_fcntl_cmd(bsm_fcntl_cmd);
	if (bfcp == NULL || bfcp->bfc_local_fcntl_cmd)
		return (-1);
	*local_fcntl_cmdp = bfcp->bfc_local_fcntl_cmd;
	return (0);
}