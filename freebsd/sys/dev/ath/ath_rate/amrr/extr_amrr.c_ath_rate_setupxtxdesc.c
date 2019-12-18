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
struct ath_softc {int /*<<< orphan*/  sc_ah; } ;
struct ath_node {int dummy; } ;
struct ath_desc {int dummy; } ;
struct amrr_node {int /*<<< orphan*/  amn_tx_try3; int /*<<< orphan*/  amn_tx_rate3sp; int /*<<< orphan*/  amn_tx_try2; int /*<<< orphan*/  amn_tx_rate2sp; int /*<<< orphan*/  amn_tx_try1; int /*<<< orphan*/  amn_tx_rate1sp; } ;

/* Variables and functions */
 struct amrr_node* ATH_NODE_AMRR (struct ath_node*) ; 
 int /*<<< orphan*/  ath_hal_setupxtxdesc (int /*<<< orphan*/ ,struct ath_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ath_rate_setupxtxdesc(struct ath_softc *sc, struct ath_node *an,
	struct ath_desc *ds, int shortPreamble, u_int8_t rix)
{
	struct amrr_node *amn = ATH_NODE_AMRR(an);

	ath_hal_setupxtxdesc(sc->sc_ah, ds
		, amn->amn_tx_rate1sp, amn->amn_tx_try1	/* series 1 */
		, amn->amn_tx_rate2sp, amn->amn_tx_try2	/* series 2 */
		, amn->amn_tx_rate3sp, amn->amn_tx_try3	/* series 3 */
	);
}