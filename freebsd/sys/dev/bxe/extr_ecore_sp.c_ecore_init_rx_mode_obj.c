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
struct ecore_rx_mode_obj {int /*<<< orphan*/  config_rx_mode; int /*<<< orphan*/  wait_comp; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 scalar_t__ CHIP_IS_E1x (struct bxe_softc*) ; 
 int /*<<< orphan*/  ecore_empty_rx_mode_wait ; 
 int /*<<< orphan*/  ecore_set_rx_mode_e1x ; 
 int /*<<< orphan*/  ecore_set_rx_mode_e2 ; 
 int /*<<< orphan*/  ecore_wait_rx_mode_comp_e2 ; 

void ecore_init_rx_mode_obj(struct bxe_softc *sc,
			    struct ecore_rx_mode_obj *o)
{
	if (CHIP_IS_E1x(sc)) {
		o->wait_comp      = ecore_empty_rx_mode_wait;
		o->config_rx_mode = ecore_set_rx_mode_e1x;
	} else {
		o->wait_comp      = ecore_wait_rx_mode_comp_e2;
		o->config_rx_mode = ecore_set_rx_mode_e2;
	}
}