#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ link_ok; } ;
struct TYPE_3__ {int caps; } ;
struct port_info {int /*<<< orphan*/  link_check_ch; TYPE_2__ link_config; TYPE_1__ phy; scalar_t__ link_fault; int /*<<< orphan*/  port_id; struct adapter* adapter; } ;
struct adapter {int /*<<< orphan*/  open_device_map; } ;

/* Variables and functions */
 int SUPPORTED_LINK_IRQ ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct port_info*) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  isset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link_check_callout ; 
 int /*<<< orphan*/  t3_link_changed (struct adapter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
check_link_status(void *arg, int pending)
{
	struct port_info *pi = arg;
	struct adapter *sc = pi->adapter;

	if (!isset(&sc->open_device_map, pi->port_id))
		return;

	t3_link_changed(sc, pi->port_id);

	if (pi->link_fault || !(pi->phy.caps & SUPPORTED_LINK_IRQ) ||
	    pi->link_config.link_ok == 0)
		callout_reset(&pi->link_check_ch, hz, link_check_callout, pi);
}