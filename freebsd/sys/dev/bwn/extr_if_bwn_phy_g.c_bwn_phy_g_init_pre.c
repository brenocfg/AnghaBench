#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int tx_bias; int /*<<< orphan*/  calib_list; } ;
struct bwn_phy_g {int pg_idletssi; int* pg_nrssi; int* pg_nrssi_lt; int pg_lofcal; int pg_initval; int pg_avgtssi; TYPE_1__ pg_loctl; int /*<<< orphan*/  pg_ofdmtab_dir; int /*<<< orphan*/  pg_immode; struct bwn_phy_g* pg_minlowsig; void* pg_tssi2dbm; } ;
struct bwn_phy {struct bwn_phy_g phy_g; } ;
struct bwn_mac {struct bwn_phy mac_phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWN_IMMODE_NONE ; 
 int /*<<< orphan*/  BWN_OFDMTAB_DIR_UNKNOWN ; 
 unsigned int N (int*) ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct bwn_phy_g*,int,int) ; 

void
bwn_phy_g_init_pre(struct bwn_mac *mac)
{
	struct bwn_phy *phy = &mac->mac_phy;
	struct bwn_phy_g *pg = &phy->phy_g;
	void *tssi2dbm;
	int idletssi;
	unsigned int i;

	tssi2dbm = pg->pg_tssi2dbm;
	idletssi = pg->pg_idletssi;

	memset(pg, 0, sizeof(*pg));

	pg->pg_tssi2dbm = tssi2dbm;
	pg->pg_idletssi = idletssi;

	memset(pg->pg_minlowsig, 0xff, sizeof(pg->pg_minlowsig));

	for (i = 0; i < N(pg->pg_nrssi); i++)
		pg->pg_nrssi[i] = -1000;
	for (i = 0; i < N(pg->pg_nrssi_lt); i++)
		pg->pg_nrssi_lt[i] = i;
	pg->pg_lofcal = 0xffff;
	pg->pg_initval = 0xffff;
	pg->pg_immode = BWN_IMMODE_NONE;
	pg->pg_ofdmtab_dir = BWN_OFDMTAB_DIR_UNKNOWN;
	pg->pg_avgtssi = 0xff;

	pg->pg_loctl.tx_bias = 0xff;
	TAILQ_INIT(&pg->pg_loctl.calib_list);
}