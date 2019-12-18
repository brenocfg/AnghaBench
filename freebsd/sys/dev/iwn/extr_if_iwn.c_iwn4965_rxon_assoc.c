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
struct iwn_rxon {int /*<<< orphan*/  rxchain; int /*<<< orphan*/  ht_dual_mask; int /*<<< orphan*/  ht_single_mask; int /*<<< orphan*/  cck_mask; int /*<<< orphan*/  ofdm_mask; int /*<<< orphan*/  filter; int /*<<< orphan*/  flags; } ;
struct iwn4965_rxon_assoc {scalar_t__ reserved; int /*<<< orphan*/  rxchain; int /*<<< orphan*/  ht_dual_mask; int /*<<< orphan*/  ht_single_mask; int /*<<< orphan*/  cck_mask; int /*<<< orphan*/  ofdm_mask; int /*<<< orphan*/  filter; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  IWN_CMD_RXON_ASSOC ; 
 int iwn_cmd (struct iwn_softc*,int /*<<< orphan*/ ,struct iwn4965_rxon_assoc*,int,int) ; 

__attribute__((used)) static int
iwn4965_rxon_assoc(struct iwn_softc *sc, int async)
{
	struct iwn4965_rxon_assoc cmd;
	struct iwn_rxon *rxon = sc->rxon;

	cmd.flags = rxon->flags;
	cmd.filter = rxon->filter;
	cmd.ofdm_mask = rxon->ofdm_mask;
	cmd.cck_mask = rxon->cck_mask;
	cmd.ht_single_mask = rxon->ht_single_mask;
	cmd.ht_dual_mask = rxon->ht_dual_mask;
	cmd.rxchain = rxon->rxchain;
	cmd.reserved = 0;

	return (iwn_cmd(sc, IWN_CMD_RXON_ASSOC, &cmd, sizeof(cmd), async));
}