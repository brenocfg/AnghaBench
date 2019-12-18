#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ sg_linearized; scalar_t__ sg_ok; scalar_t__ tx_flow_control_xoff; scalar_t__ tx_flow_control_xon; scalar_t__ tx_kicks; scalar_t__ tx_restart_queue; scalar_t__ tx_timeout_count; scalar_t__ rx_encaps_errors; scalar_t__ tx_queue_running_average; scalar_t__ tx_queue_max; scalar_t__ rx_queue_running_average; scalar_t__ rx_queue_max; } ;
struct vector_private {TYPE_1__ estats; } ;

/* Variables and functions */

__attribute__((used)) static void vector_reset_stats(struct vector_private *vp)
{
	vp->estats.rx_queue_max = 0;
	vp->estats.rx_queue_running_average = 0;
	vp->estats.tx_queue_max = 0;
	vp->estats.tx_queue_running_average = 0;
	vp->estats.rx_encaps_errors = 0;
	vp->estats.tx_timeout_count = 0;
	vp->estats.tx_restart_queue = 0;
	vp->estats.tx_kicks = 0;
	vp->estats.tx_flow_control_xon = 0;
	vp->estats.tx_flow_control_xoff = 0;
	vp->estats.sg_ok = 0;
	vp->estats.sg_linearized = 0;
}