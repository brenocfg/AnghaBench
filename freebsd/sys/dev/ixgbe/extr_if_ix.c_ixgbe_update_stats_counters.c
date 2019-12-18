#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
struct ixgbe_hw_stats {int crcerrs; int rlec; int gotc; int gptc; int mptc; int ptc64; int /*<<< orphan*/  mprc; int /*<<< orphan*/  gorc; int /*<<< orphan*/  gprc; int /*<<< orphan*/  fcoedwtc; int /*<<< orphan*/  fcoedwrc; int /*<<< orphan*/  fcoeptc; int /*<<< orphan*/  fcoeprc; int /*<<< orphan*/  fcoerpdc; int /*<<< orphan*/  fclast; int /*<<< orphan*/  fccrc; int /*<<< orphan*/  xec; int /*<<< orphan*/  bptc; int /*<<< orphan*/  ptc1522; int /*<<< orphan*/  ptc1023; int /*<<< orphan*/  ptc511; int /*<<< orphan*/  ptc255; int /*<<< orphan*/  ptc127; int /*<<< orphan*/  tpt; int /*<<< orphan*/  tpr; int /*<<< orphan*/  mngptc; int /*<<< orphan*/  mngpdc; int /*<<< orphan*/  mngprc; int /*<<< orphan*/  rjc; int /*<<< orphan*/  roc; int /*<<< orphan*/  rfc; int /*<<< orphan*/  ruc; int /*<<< orphan*/  lxofftxc; int /*<<< orphan*/  lxontxc; int /*<<< orphan*/  prc1522; int /*<<< orphan*/  prc1023; int /*<<< orphan*/  prc511; int /*<<< orphan*/  prc255; int /*<<< orphan*/  prc127; int /*<<< orphan*/  prc64; int /*<<< orphan*/  bprc; int /*<<< orphan*/  tor; int /*<<< orphan*/  lxoffrxc; int /*<<< orphan*/  lxonrxc; int /*<<< orphan*/  mrfc; int /*<<< orphan*/  mlfc; int /*<<< orphan*/ * qprdc; int /*<<< orphan*/ * qptc; int /*<<< orphan*/ * qprc; int /*<<< orphan*/ * mpc; int /*<<< orphan*/  mspdc; int /*<<< orphan*/  errbc; int /*<<< orphan*/  illerrc; } ;
struct TYPE_5__ {scalar_t__ type; } ;
struct ixgbe_hw {TYPE_2__ mac; } ;
struct TYPE_4__ {struct ixgbe_hw_stats pf; } ;
struct adapter {TYPE_3__* shared; TYPE_1__ stats; struct ixgbe_hw hw; } ;
struct TYPE_6__ {int isc_pause_frames; } ;

/* Variables and functions */
 int ETHER_MIN_LEN ; 
 int /*<<< orphan*/  IXGBE_BPRC ; 
 int /*<<< orphan*/  IXGBE_BPTC ; 
 int /*<<< orphan*/  IXGBE_CRCERRS ; 
 int /*<<< orphan*/  IXGBE_ERRBC ; 
 int /*<<< orphan*/  IXGBE_FCCRC ; 
 int /*<<< orphan*/  IXGBE_FCLAST ; 
 int /*<<< orphan*/  IXGBE_FCOEDWRC ; 
 int /*<<< orphan*/  IXGBE_FCOEDWTC ; 
 int /*<<< orphan*/  IXGBE_FCOEPRC ; 
 int /*<<< orphan*/  IXGBE_FCOEPTC ; 
 int /*<<< orphan*/  IXGBE_FCOERPDC ; 
 int /*<<< orphan*/  IXGBE_GORCH ; 
 int /*<<< orphan*/  IXGBE_GORCL ; 
 int /*<<< orphan*/  IXGBE_GOTCH ; 
 int /*<<< orphan*/  IXGBE_GOTCL ; 
 int /*<<< orphan*/  IXGBE_GPRC ; 
 int /*<<< orphan*/  IXGBE_GPTC ; 
 int /*<<< orphan*/  IXGBE_ILLERRC ; 
 int /*<<< orphan*/  IXGBE_LXOFFRXC ; 
 int /*<<< orphan*/  IXGBE_LXOFFRXCNT ; 
 int /*<<< orphan*/  IXGBE_LXOFFTXC ; 
 int /*<<< orphan*/  IXGBE_LXONRXC ; 
 int /*<<< orphan*/  IXGBE_LXONRXCNT ; 
 int /*<<< orphan*/  IXGBE_LXONTXC ; 
 int /*<<< orphan*/  IXGBE_MLFC ; 
 int /*<<< orphan*/  IXGBE_MNGPDC ; 
 int /*<<< orphan*/  IXGBE_MNGPRC ; 
 int /*<<< orphan*/  IXGBE_MNGPTC ; 
 int /*<<< orphan*/  IXGBE_MPC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_MPRC ; 
 int /*<<< orphan*/  IXGBE_MPTC ; 
 int /*<<< orphan*/  IXGBE_MRFC ; 
 int /*<<< orphan*/  IXGBE_MSPDC ; 
 int /*<<< orphan*/  IXGBE_PRC1023 ; 
 int /*<<< orphan*/  IXGBE_PRC127 ; 
 int /*<<< orphan*/  IXGBE_PRC1522 ; 
 int /*<<< orphan*/  IXGBE_PRC255 ; 
 int /*<<< orphan*/  IXGBE_PRC511 ; 
 int /*<<< orphan*/  IXGBE_PRC64 ; 
 int /*<<< orphan*/  IXGBE_PTC1023 ; 
 int /*<<< orphan*/  IXGBE_PTC127 ; 
 int /*<<< orphan*/  IXGBE_PTC1522 ; 
 int /*<<< orphan*/  IXGBE_PTC255 ; 
 int /*<<< orphan*/  IXGBE_PTC511 ; 
 int /*<<< orphan*/  IXGBE_PTC64 ; 
 int /*<<< orphan*/  IXGBE_QPRC (int) ; 
 int /*<<< orphan*/  IXGBE_QPRDC (int) ; 
 int /*<<< orphan*/  IXGBE_QPTC (int) ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_RFC ; 
 int /*<<< orphan*/  IXGBE_RJC ; 
 int /*<<< orphan*/  IXGBE_RLEC ; 
 int /*<<< orphan*/  IXGBE_ROC ; 
 int /*<<< orphan*/  IXGBE_RUC ; 
 int /*<<< orphan*/  IXGBE_SET_COLLISIONS (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_SET_IBYTES (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_SET_IERRORS (struct adapter*,int) ; 
 int /*<<< orphan*/  IXGBE_SET_IMCASTS (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_SET_IPACKETS (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_SET_IQDROPS (struct adapter*,int) ; 
 int /*<<< orphan*/  IXGBE_SET_OBYTES (struct adapter*,int) ; 
 int /*<<< orphan*/  IXGBE_SET_OMCASTS (struct adapter*,int) ; 
 int /*<<< orphan*/  IXGBE_SET_OPACKETS (struct adapter*,int) ; 
 int /*<<< orphan*/  IXGBE_TORH ; 
 int /*<<< orphan*/  IXGBE_TORL ; 
 int /*<<< orphan*/  IXGBE_TPR ; 
 int /*<<< orphan*/  IXGBE_TPT ; 
 int /*<<< orphan*/  IXGBE_XEC ; 
 scalar_t__ ixgbe_mac_82598EB ; 

__attribute__((used)) static void
ixgbe_update_stats_counters(struct adapter *adapter)
{
	struct ixgbe_hw       *hw = &adapter->hw;
	struct ixgbe_hw_stats *stats = &adapter->stats.pf;
	u32                   missed_rx = 0, bprc, lxon, lxoff, total;
	u32                   lxoffrxc;
	u64                   total_missed_rx = 0;

	stats->crcerrs += IXGBE_READ_REG(hw, IXGBE_CRCERRS);
	stats->illerrc += IXGBE_READ_REG(hw, IXGBE_ILLERRC);
	stats->errbc += IXGBE_READ_REG(hw, IXGBE_ERRBC);
	stats->mspdc += IXGBE_READ_REG(hw, IXGBE_MSPDC);
	stats->mpc[0] += IXGBE_READ_REG(hw, IXGBE_MPC(0));

	for (int i = 0; i < 16; i++) {
		stats->qprc[i] += IXGBE_READ_REG(hw, IXGBE_QPRC(i));
		stats->qptc[i] += IXGBE_READ_REG(hw, IXGBE_QPTC(i));
		stats->qprdc[i] += IXGBE_READ_REG(hw, IXGBE_QPRDC(i));
	}
	stats->mlfc += IXGBE_READ_REG(hw, IXGBE_MLFC);
	stats->mrfc += IXGBE_READ_REG(hw, IXGBE_MRFC);
	stats->rlec += IXGBE_READ_REG(hw, IXGBE_RLEC);

	/* Hardware workaround, gprc counts missed packets */
	stats->gprc += IXGBE_READ_REG(hw, IXGBE_GPRC);
	stats->gprc -= missed_rx;

	if (hw->mac.type != ixgbe_mac_82598EB) {
		stats->gorc += IXGBE_READ_REG(hw, IXGBE_GORCL) +
		    ((u64)IXGBE_READ_REG(hw, IXGBE_GORCH) << 32);
		stats->gotc += IXGBE_READ_REG(hw, IXGBE_GOTCL) +
		    ((u64)IXGBE_READ_REG(hw, IXGBE_GOTCH) << 32);
		stats->tor += IXGBE_READ_REG(hw, IXGBE_TORL) +
		    ((u64)IXGBE_READ_REG(hw, IXGBE_TORH) << 32);
		stats->lxonrxc += IXGBE_READ_REG(hw, IXGBE_LXONRXCNT);
		lxoffrxc = IXGBE_READ_REG(hw, IXGBE_LXOFFRXCNT);
		stats->lxoffrxc += lxoffrxc;
	} else {
		stats->lxonrxc += IXGBE_READ_REG(hw, IXGBE_LXONRXC);
		lxoffrxc = IXGBE_READ_REG(hw, IXGBE_LXOFFRXC);
		stats->lxoffrxc += lxoffrxc;
		/* 82598 only has a counter in the high register */
		stats->gorc += IXGBE_READ_REG(hw, IXGBE_GORCH);
		stats->gotc += IXGBE_READ_REG(hw, IXGBE_GOTCH);
		stats->tor += IXGBE_READ_REG(hw, IXGBE_TORH);
	}

	/*
	 * For watchdog management we need to know if we have been paused
	 * during the last interval, so capture that here.
	*/
	if (lxoffrxc)
		adapter->shared->isc_pause_frames = 1;

	/*
	 * Workaround: mprc hardware is incorrectly counting
	 * broadcasts, so for now we subtract those.
	 */
	bprc = IXGBE_READ_REG(hw, IXGBE_BPRC);
	stats->bprc += bprc;
	stats->mprc += IXGBE_READ_REG(hw, IXGBE_MPRC);
	if (hw->mac.type == ixgbe_mac_82598EB)
		stats->mprc -= bprc;

	stats->prc64 += IXGBE_READ_REG(hw, IXGBE_PRC64);
	stats->prc127 += IXGBE_READ_REG(hw, IXGBE_PRC127);
	stats->prc255 += IXGBE_READ_REG(hw, IXGBE_PRC255);
	stats->prc511 += IXGBE_READ_REG(hw, IXGBE_PRC511);
	stats->prc1023 += IXGBE_READ_REG(hw, IXGBE_PRC1023);
	stats->prc1522 += IXGBE_READ_REG(hw, IXGBE_PRC1522);

	lxon = IXGBE_READ_REG(hw, IXGBE_LXONTXC);
	stats->lxontxc += lxon;
	lxoff = IXGBE_READ_REG(hw, IXGBE_LXOFFTXC);
	stats->lxofftxc += lxoff;
	total = lxon + lxoff;

	stats->gptc += IXGBE_READ_REG(hw, IXGBE_GPTC);
	stats->mptc += IXGBE_READ_REG(hw, IXGBE_MPTC);
	stats->ptc64 += IXGBE_READ_REG(hw, IXGBE_PTC64);
	stats->gptc -= total;
	stats->mptc -= total;
	stats->ptc64 -= total;
	stats->gotc -= total * ETHER_MIN_LEN;

	stats->ruc += IXGBE_READ_REG(hw, IXGBE_RUC);
	stats->rfc += IXGBE_READ_REG(hw, IXGBE_RFC);
	stats->roc += IXGBE_READ_REG(hw, IXGBE_ROC);
	stats->rjc += IXGBE_READ_REG(hw, IXGBE_RJC);
	stats->mngprc += IXGBE_READ_REG(hw, IXGBE_MNGPRC);
	stats->mngpdc += IXGBE_READ_REG(hw, IXGBE_MNGPDC);
	stats->mngptc += IXGBE_READ_REG(hw, IXGBE_MNGPTC);
	stats->tpr += IXGBE_READ_REG(hw, IXGBE_TPR);
	stats->tpt += IXGBE_READ_REG(hw, IXGBE_TPT);
	stats->ptc127 += IXGBE_READ_REG(hw, IXGBE_PTC127);
	stats->ptc255 += IXGBE_READ_REG(hw, IXGBE_PTC255);
	stats->ptc511 += IXGBE_READ_REG(hw, IXGBE_PTC511);
	stats->ptc1023 += IXGBE_READ_REG(hw, IXGBE_PTC1023);
	stats->ptc1522 += IXGBE_READ_REG(hw, IXGBE_PTC1522);
	stats->bptc += IXGBE_READ_REG(hw, IXGBE_BPTC);
	stats->xec += IXGBE_READ_REG(hw, IXGBE_XEC);
	stats->fccrc += IXGBE_READ_REG(hw, IXGBE_FCCRC);
	stats->fclast += IXGBE_READ_REG(hw, IXGBE_FCLAST);
	/* Only read FCOE on 82599 */
	if (hw->mac.type != ixgbe_mac_82598EB) {
		stats->fcoerpdc += IXGBE_READ_REG(hw, IXGBE_FCOERPDC);
		stats->fcoeprc += IXGBE_READ_REG(hw, IXGBE_FCOEPRC);
		stats->fcoeptc += IXGBE_READ_REG(hw, IXGBE_FCOEPTC);
		stats->fcoedwrc += IXGBE_READ_REG(hw, IXGBE_FCOEDWRC);
		stats->fcoedwtc += IXGBE_READ_REG(hw, IXGBE_FCOEDWTC);
	}

	/* Fill out the OS statistics structure */
	IXGBE_SET_IPACKETS(adapter, stats->gprc);
	IXGBE_SET_OPACKETS(adapter, stats->gptc);
	IXGBE_SET_IBYTES(adapter, stats->gorc);
	IXGBE_SET_OBYTES(adapter, stats->gotc);
	IXGBE_SET_IMCASTS(adapter, stats->mprc);
	IXGBE_SET_OMCASTS(adapter, stats->mptc);
	IXGBE_SET_COLLISIONS(adapter, 0);
	IXGBE_SET_IQDROPS(adapter, total_missed_rx);
	IXGBE_SET_IERRORS(adapter, stats->crcerrs + stats->rlec);
}