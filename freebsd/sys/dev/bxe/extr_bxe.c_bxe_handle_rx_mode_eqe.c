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
typedef  union event_ring_elem {int dummy; } event_ring_elem ;
struct bxe_softc {int /*<<< orphan*/  sp_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECORE_FILTER_RX_MODE_PENDING ; 
 int /*<<< orphan*/  ECORE_FILTER_RX_MODE_SCHED ; 
 int /*<<< orphan*/  bxe_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bxe_set_storm_rx_mode (struct bxe_softc*) ; 
 scalar_t__ bxe_test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bxe_handle_rx_mode_eqe(struct bxe_softc      *sc,
                       union event_ring_elem *elem)
{
    bxe_clear_bit(ECORE_FILTER_RX_MODE_PENDING, &sc->sp_state);

    /* send rx_mode command again if was requested */
    if (bxe_test_and_clear_bit(ECORE_FILTER_RX_MODE_SCHED,
                               &sc->sp_state)) {
        bxe_set_storm_rx_mode(sc);
    }
}