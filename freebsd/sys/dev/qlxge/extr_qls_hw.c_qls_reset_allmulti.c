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
typedef  int /*<<< orphan*/  qla_host_t ;

/* Variables and functions */
 int Q81_CTL_RI_DST_DFLTQ ; 
 int Q81_CTL_RI_IDX_ALLMULTI ; 
 int Q81_CTL_RI_TYPE_NICQMASK ; 
 int qls_load_route_idx_reg_locked (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

void
qls_reset_allmulti(qla_host_t *ha)
{
	int ret;

	ret = qls_load_route_idx_reg_locked(ha, (Q81_CTL_RI_TYPE_NICQMASK |
			Q81_CTL_RI_IDX_ALLMULTI | Q81_CTL_RI_DST_DFLTQ), 0);
	return;
}