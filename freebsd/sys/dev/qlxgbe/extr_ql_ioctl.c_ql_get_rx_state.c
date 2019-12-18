#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int num_rds_rings; TYPE_2__* rds; } ;
struct TYPE_9__ {TYPE_1__ hw; } ;
typedef  TYPE_3__ qla_host_t ;
struct TYPE_10__ {int /*<<< orphan*/  rx_next; int /*<<< orphan*/  prod_std; } ;
typedef  TYPE_4__ qla_drvr_state_rx_t ;
struct TYPE_8__ {int /*<<< orphan*/  rx_next; int /*<<< orphan*/  prod_std; } ;

/* Variables and functions */

__attribute__((used)) static void
ql_get_rx_state(qla_host_t *ha, qla_drvr_state_rx_t *rx_state)
{
	int i;

	for (i = 0; i < ha->hw.num_rds_rings; i++) {
		rx_state->prod_std = ha->hw.rds[i].prod_std;
		rx_state->rx_next = ha->hw.rds[i].rx_next;
		rx_state++;
	}
	return;
}