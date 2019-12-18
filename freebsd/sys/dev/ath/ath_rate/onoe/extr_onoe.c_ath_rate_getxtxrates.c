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
typedef  int /*<<< orphan*/  uint8_t ;
struct onoe_node {int on_tx_try0; int /*<<< orphan*/  on_tx_rate3; int /*<<< orphan*/  on_tx_rate2; int /*<<< orphan*/  on_tx_rate1; int /*<<< orphan*/  on_tx_rate0; } ;
struct ath_softc {int dummy; } ;
struct ath_rc_series {int tries; int /*<<< orphan*/  rix; scalar_t__ flags; } ;
struct ath_node {int dummy; } ;

/* Variables and functions */
 struct onoe_node* ATH_NODE_ONOE (struct ath_node*) ; 

void
ath_rate_getxtxrates(struct ath_softc *sc, struct ath_node *an,
    uint8_t rix0, struct ath_rc_series *rc)
{
	struct onoe_node *on = ATH_NODE_ONOE(an);

	rc[0].flags = rc[1].flags = rc[2].flags = rc[3].flags = 0;

	rc[0].rix = on->on_tx_rate0;
	rc[1].rix = on->on_tx_rate1;
	rc[2].rix = on->on_tx_rate2;
	rc[3].rix = on->on_tx_rate3;

	rc[0].tries = on->on_tx_try0;
	rc[1].tries = 2;
	rc[2].tries = 2;
	rc[3].tries = 2;
}