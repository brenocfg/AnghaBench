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
struct iwn_softc {struct iwn_rxon* rxon; } ;
struct iwn_rxon {int /*<<< orphan*/  acquisition; int /*<<< orphan*/  rxchain; int /*<<< orphan*/  ht_triple_mask; int /*<<< orphan*/  ht_dual_mask; int /*<<< orphan*/  ht_single_mask; int /*<<< orphan*/  cck_mask; int /*<<< orphan*/  ofdm_mask; int /*<<< orphan*/  filter; int /*<<< orphan*/  flags; } ;
struct iwn5000_rxon_assoc {scalar_t__ reserved3; int /*<<< orphan*/  acquisition; int /*<<< orphan*/  rxchain; scalar_t__ reserved2; int /*<<< orphan*/  ht_triple_mask; int /*<<< orphan*/  ht_dual_mask; int /*<<< orphan*/  ht_single_mask; scalar_t__ reserved1; int /*<<< orphan*/  cck_mask; int /*<<< orphan*/  ofdm_mask; int /*<<< orphan*/  filter; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  IWN_CMD_RXON_ASSOC ; 
 int iwn_cmd (struct iwn_softc*,int /*<<< orphan*/ ,struct iwn5000_rxon_assoc*,int,int) ; 

__attribute__((used)) static int
iwn5000_rxon_assoc(struct iwn_softc *sc, int async)
{
	struct iwn5000_rxon_assoc cmd;
	struct iwn_rxon *rxon = sc->rxon;

	cmd.flags = rxon->flags;
	cmd.filter = rxon->filter;
	cmd.ofdm_mask = rxon->ofdm_mask;
	cmd.cck_mask = rxon->cck_mask;
	cmd.reserved1 = 0;
	cmd.ht_single_mask = rxon->ht_single_mask;
	cmd.ht_dual_mask = rxon->ht_dual_mask;
	cmd.ht_triple_mask = rxon->ht_triple_mask;
	cmd.reserved2 = 0;
	cmd.rxchain = rxon->rxchain;
	cmd.acquisition = rxon->acquisition;
	cmd.reserved3 = 0;

	return (iwn_cmd(sc, IWN_CMD_RXON_ASSOC, &cmd, sizeof(cmd), async));
}