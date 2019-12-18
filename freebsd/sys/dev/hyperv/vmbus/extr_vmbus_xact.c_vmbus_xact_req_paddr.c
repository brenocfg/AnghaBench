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
struct TYPE_2__ {int /*<<< orphan*/  hv_paddr; } ;
struct vmbus_xact {TYPE_1__ x_req_dma; } ;
typedef  int /*<<< orphan*/  bus_addr_t ;

/* Variables and functions */

bus_addr_t
vmbus_xact_req_paddr(const struct vmbus_xact *xact)
{

	return (xact->x_req_dma.hv_paddr);
}