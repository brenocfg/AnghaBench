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
struct ath_softc {int dummy; } ;
struct ath_node {int an_is_powersave; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH_TX_LOCK_ASSERT (struct ath_softc*) ; 

int
ath_tx_node_is_asleep(struct ath_softc *sc, struct ath_node *an)
{

	ATH_TX_LOCK_ASSERT(sc);

	return (an->an_is_powersave);
}