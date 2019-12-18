#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int aen_mb0; int /*<<< orphan*/  aen_mb4; int /*<<< orphan*/  aen_mb3; int /*<<< orphan*/  aen_mb2; int /*<<< orphan*/  aen_mb1; } ;
struct TYPE_6__ {TYPE_1__ hw; } ;
typedef  TYPE_2__ qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  qla_idc_ack (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
qla_hw_async_event(qla_host_t *ha)
{
        switch (ha->hw.aen_mb0) {
        case 0x8101:
                (void)qla_idc_ack(ha, ha->hw.aen_mb1, ha->hw.aen_mb2,
                        ha->hw.aen_mb3, ha->hw.aen_mb4);

                break;

        default:
                break;
        }

        return;
}