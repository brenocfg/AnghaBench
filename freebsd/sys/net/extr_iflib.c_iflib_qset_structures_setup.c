#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* if_ctx_t ;
struct TYPE_5__ {int /*<<< orphan*/  ifc_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int iflib_rx_structures_setup (TYPE_1__*) ; 
 int iflib_tx_structures_setup (TYPE_1__*) ; 

__attribute__((used)) static int
iflib_qset_structures_setup(if_ctx_t ctx)
{
	int err;

	/*
	 * It is expected that the caller takes care of freeing queues if this
	 * fails.
	 */
	if ((err = iflib_tx_structures_setup(ctx)) != 0) {
		device_printf(ctx->ifc_dev, "iflib_tx_structures_setup failed: %d\n", err);
		return (err);
	}

	if ((err = iflib_rx_structures_setup(ctx)) != 0)
		device_printf(ctx->ifc_dev, "iflib_rx_structures_setup failed: %d\n", err);

	return (err);
}