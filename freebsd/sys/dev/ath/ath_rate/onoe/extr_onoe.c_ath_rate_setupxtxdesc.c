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
struct onoe_node {int /*<<< orphan*/  on_tx_rate3sp; int /*<<< orphan*/  on_tx_rate2sp; int /*<<< orphan*/  on_tx_rate1sp; } ;
struct ath_softc {int /*<<< orphan*/  sc_ah; } ;
struct ath_node {int dummy; } ;
struct ath_desc {int dummy; } ;

/* Variables and functions */
 struct onoe_node* ATH_NODE_ONOE (struct ath_node*) ; 
 int /*<<< orphan*/  ath_hal_setupxtxdesc (int /*<<< orphan*/ ,struct ath_desc*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

void
ath_rate_setupxtxdesc(struct ath_softc *sc, struct ath_node *an,
	struct ath_desc *ds, int shortPreamble, u_int8_t rix)
{
	struct onoe_node *on = ATH_NODE_ONOE(an);

	ath_hal_setupxtxdesc(sc->sc_ah, ds
		, on->on_tx_rate1sp, 2	/* series 1 */
		, on->on_tx_rate2sp, 2	/* series 2 */
		, on->on_tx_rate3sp, 2	/* series 3 */
	);
}