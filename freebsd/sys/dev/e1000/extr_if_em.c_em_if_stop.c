#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ type; } ;
struct TYPE_7__ {TYPE_1__ mac; } ;
struct adapter {TYPE_2__ hw; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_WRITE_REG (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E1000_WUFC ; 
 int /*<<< orphan*/  INIT_DEBUGOUT (char*) ; 
 scalar_t__ e1000_82544 ; 
 int /*<<< orphan*/  e1000_cleanup_led (TYPE_2__*) ; 
 int /*<<< orphan*/  e1000_led_off (TYPE_2__*) ; 
 int /*<<< orphan*/  e1000_reset_hw (TYPE_2__*) ; 
 struct adapter* iflib_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
em_if_stop(if_ctx_t ctx)
{
	struct adapter *adapter = iflib_get_softc(ctx);

	INIT_DEBUGOUT("em_if_stop: begin");

	e1000_reset_hw(&adapter->hw);
	if (adapter->hw.mac.type >= e1000_82544)
		E1000_WRITE_REG(&adapter->hw, E1000_WUFC, 0);

	e1000_led_off(&adapter->hw);
	e1000_cleanup_led(&adapter->hw);
}