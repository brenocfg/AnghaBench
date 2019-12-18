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
 int /*<<< orphan*/  qlnx_add_drvr_rds_stats (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qlnx_add_drvr_sds_stats (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qlnx_add_drvr_tx_stats (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
qlnx_add_drvr_stats_sysctls(qla_host_t *ha)
{
	qlnx_add_drvr_sds_stats(ha);
	qlnx_add_drvr_rds_stats(ha);
	qlnx_add_drvr_tx_stats(ha);
	return;
}