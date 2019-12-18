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
typedef  int /*<<< orphan*/  u_int8_t ;
struct ath_softc {int dummy; } ;
struct ath_node {int dummy; } ;
struct amrr_node {int amn_tx_try0; int /*<<< orphan*/  amn_tx_rate0; int /*<<< orphan*/  amn_tx_rate0sp; int /*<<< orphan*/  amn_tx_rix0; } ;

/* Variables and functions */
 struct amrr_node* ATH_NODE_AMRR (struct ath_node*) ; 

void
ath_rate_findrate(struct ath_softc *sc, struct ath_node *an,
	int shortPreamble, size_t frameLen,
	u_int8_t *rix, int *try0, u_int8_t *txrate)
{
	struct amrr_node *amn = ATH_NODE_AMRR(an);

	*rix = amn->amn_tx_rix0;
	*try0 = amn->amn_tx_try0;
	if (shortPreamble)
		*txrate = amn->amn_tx_rate0sp;
	else
		*txrate = amn->amn_tx_rate0;
}