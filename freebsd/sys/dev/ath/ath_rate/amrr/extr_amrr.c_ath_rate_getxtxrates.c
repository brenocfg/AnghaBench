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
struct ath_softc {int dummy; } ;
struct ath_rc_series {int /*<<< orphan*/  tries; int /*<<< orphan*/  rix; scalar_t__ flags; } ;
struct ath_node {int dummy; } ;
struct amrr_node {int /*<<< orphan*/  amn_tx_try3; int /*<<< orphan*/  amn_tx_try2; int /*<<< orphan*/  amn_tx_try1; int /*<<< orphan*/  amn_tx_try0; int /*<<< orphan*/  amn_tx_rate3; int /*<<< orphan*/  amn_tx_rate2; int /*<<< orphan*/  amn_tx_rate1; int /*<<< orphan*/  amn_tx_rate0; } ;

/* Variables and functions */
 struct amrr_node* ATH_NODE_AMRR (struct ath_node*) ; 

void
ath_rate_getxtxrates(struct ath_softc *sc, struct ath_node *an,
    uint8_t rix0, struct ath_rc_series *rc)
{
	struct amrr_node *amn = ATH_NODE_AMRR(an);

	rc[0].flags = rc[1].flags = rc[2].flags = rc[3].flags = 0;

	rc[0].rix = amn->amn_tx_rate0;
	rc[1].rix = amn->amn_tx_rate1;
	rc[2].rix = amn->amn_tx_rate2;
	rc[3].rix = amn->amn_tx_rate3;

	rc[0].tries = amn->amn_tx_try0;
	rc[1].tries = amn->amn_tx_try1;
	rc[2].tries = amn->amn_tx_try2;
	rc[3].tries = amn->amn_tx_try3;
}