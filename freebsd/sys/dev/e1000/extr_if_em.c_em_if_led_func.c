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
struct adapter {int /*<<< orphan*/  hw; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  e1000_cleanup_led (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  e1000_led_off (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  e1000_led_on (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  e1000_setup_led (int /*<<< orphan*/ *) ; 
 struct adapter* iflib_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
em_if_led_func(if_ctx_t ctx, int onoff)
{
	struct adapter *adapter = iflib_get_softc(ctx);

	if (onoff) {
		e1000_setup_led(&adapter->hw);
		e1000_led_on(&adapter->hw);
	} else {
		e1000_led_off(&adapter->hw);
		e1000_cleanup_led(&adapter->hw);
	}
}