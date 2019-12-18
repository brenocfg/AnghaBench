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
struct ecore_rx_mode_ramrod_params {int /*<<< orphan*/  pstate; int /*<<< orphan*/  state; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int ecore_state_wait (struct bxe_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ecore_wait_rx_mode_comp_e2(struct bxe_softc *sc,
				      struct ecore_rx_mode_ramrod_params *p)
{
	return ecore_state_wait(sc, p->state, p->pstate);
}