#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
struct wrq_cookie {int dummy; } ;
struct TYPE_10__ {int pfvf_vld; int ovlan_vld; int ethtype; int vlan; int vnic; int dport; int sport; int /*<<< orphan*/  sip; int /*<<< orphan*/  dip; int /*<<< orphan*/  tos; int /*<<< orphan*/  proto; int /*<<< orphan*/  matchtype; int /*<<< orphan*/  iport; int /*<<< orphan*/  fcoe; int /*<<< orphan*/  macidx; int /*<<< orphan*/  vlan_vld; int /*<<< orphan*/  frag; } ;
struct TYPE_9__ {int pfvf_vld; int ovlan_vld; int ethtype; int vlan; int vnic; int dport; int sport; int /*<<< orphan*/  sip; int /*<<< orphan*/  dip; int /*<<< orphan*/  tos; int /*<<< orphan*/  proto; int /*<<< orphan*/  matchtype; int /*<<< orphan*/  iport; int /*<<< orphan*/  fcoe; int /*<<< orphan*/  macidx; int /*<<< orphan*/  vlan_vld; int /*<<< orphan*/  frag; } ;
struct TYPE_12__ {scalar_t__ action; scalar_t__ newvlan; int nat_dport; int nat_sport; int nat_seq_chk; int /*<<< orphan*/  nat_sip; int /*<<< orphan*/  nat_dip; scalar_t__ nat_mode; int /*<<< orphan*/  nat_flag_chk; int /*<<< orphan*/  swapmac; TYPE_3__ mask; TYPE_2__ val; scalar_t__ prio; int /*<<< orphan*/  eport; int /*<<< orphan*/  hitcnts; int /*<<< orphan*/  newsmac; int /*<<< orphan*/  newdmac; int /*<<< orphan*/  dirsteerhash; int /*<<< orphan*/  maskhash; int /*<<< orphan*/  dirsteer; int /*<<< orphan*/  rpttid; int /*<<< orphan*/  iq; scalar_t__ type; int /*<<< orphan*/  hash; } ;
struct t4_filter {size_t idx; TYPE_5__ fs; } ;
struct smt_entry {int dummy; } ;
struct l2t_entry {int /*<<< orphan*/  idx; } ;
struct fw_filter_wr {int dummy; } ;
struct fw_filter2_wr {int frag_to_ovlan_vldm; int natmode_to_ulp_type; void* natseqcheck; void* newfport; void* newlport; int /*<<< orphan*/  newfip; int /*<<< orphan*/  newlip; int /*<<< orphan*/  filter_type_swapmac; struct fw_filter2_wr* sma; void* fpm; void* fp; void* lpm; void* lp; int /*<<< orphan*/  fipm; int /*<<< orphan*/  fip; int /*<<< orphan*/  lipm; int /*<<< orphan*/  lip; void* ovlanm; void* ovlan; void* ivlanm; void* ivlan; int /*<<< orphan*/  ttypm; int /*<<< orphan*/  ttyp; int /*<<< orphan*/  ptclm; int /*<<< orphan*/  ptcl; void* maci_to_matchtypem; void* rx_chan_rx_rpl_iq; scalar_t__ smac_sel; void* ethtypem; void* ethtype; void* del_filter_to_l2tix; void* tid_to_iq; void* len16_pkd; void* op_pkd; } ;
struct filter_entry {int pending; int valid; int tid; TYPE_5__ fs; struct l2t_entry* l2te; struct smt_entry* smt; scalar_t__ locked; } ;
struct TYPE_14__ {size_t nhpftids; int hpftid_base; size_t nftids; int ftid_base; int /*<<< orphan*/  ftid_lock; int /*<<< orphan*/  ftid_cv; int /*<<< orphan*/  ftids_in_use; int /*<<< orphan*/  hpftids_in_use; struct filter_entry* ftid_tab; struct filter_entry* hpftid_tab; } ;
struct TYPE_8__ {int /*<<< orphan*/  abs_id; } ;
struct TYPE_13__ {int /*<<< orphan*/ * ctrlq; TYPE_1__ fwq; } ;
struct TYPE_11__ {scalar_t__ filter2_wr_support; } ;
struct adapter {TYPE_7__ tids; TYPE_6__ sge; TYPE_4__ params; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINPROGRESS ; 
 int EIO ; 
 int ENOMEM ; 
 int EPERM ; 
 scalar_t__ FILTER_DROP ; 
 scalar_t__ FILTER_SWITCH ; 
 int /*<<< orphan*/  FW_FILTER2_WR ; 
 int /*<<< orphan*/  FW_FILTER_WR ; 
 int FW_LEN16 (struct fw_filter2_wr) ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  ULP_MODE_NONE ; 
 int /*<<< orphan*/  ULP_MODE_TCPDDP ; 
 scalar_t__ VLAN_INSERT ; 
 scalar_t__ VLAN_REMOVE ; 
 scalar_t__ VLAN_REWRITE ; 
 int V_FW_FILTER2_WR_NATFLAGCHECK (int /*<<< orphan*/ ) ; 
 int V_FW_FILTER2_WR_NATMODE (scalar_t__) ; 
 int /*<<< orphan*/  V_FW_FILTER2_WR_SWAPMAC (int /*<<< orphan*/ ) ; 
 int V_FW_FILTER2_WR_ULP_TYPE (int /*<<< orphan*/ ) ; 
 int V_FW_FILTER_WR_DIRSTEER (int /*<<< orphan*/ ) ; 
 int V_FW_FILTER_WR_DIRSTEERHASH (int /*<<< orphan*/ ) ; 
 int V_FW_FILTER_WR_DMAC (int /*<<< orphan*/ ) ; 
 int V_FW_FILTER_WR_DROP (int) ; 
 int V_FW_FILTER_WR_FCOE (int /*<<< orphan*/ ) ; 
 int V_FW_FILTER_WR_FCOEM (int /*<<< orphan*/ ) ; 
 int V_FW_FILTER_WR_FRAG (int /*<<< orphan*/ ) ; 
 int V_FW_FILTER_WR_FRAGM (int /*<<< orphan*/ ) ; 
 int V_FW_FILTER_WR_HITCNTS (int /*<<< orphan*/ ) ; 
 int V_FW_FILTER_WR_INSVLAN (int) ; 
 int V_FW_FILTER_WR_IQ (int /*<<< orphan*/ ) ; 
 int V_FW_FILTER_WR_IVLAN_VLD (int /*<<< orphan*/ ) ; 
 int V_FW_FILTER_WR_IVLAN_VLDM (int /*<<< orphan*/ ) ; 
 int V_FW_FILTER_WR_L2TIX (int /*<<< orphan*/ ) ; 
 int V_FW_FILTER_WR_LPBK (int) ; 
 int V_FW_FILTER_WR_MACI (int /*<<< orphan*/ ) ; 
 int V_FW_FILTER_WR_MACIM (int /*<<< orphan*/ ) ; 
 int V_FW_FILTER_WR_MASKHASH (int /*<<< orphan*/ ) ; 
 int V_FW_FILTER_WR_MATCHTYPE (int /*<<< orphan*/ ) ; 
 int V_FW_FILTER_WR_MATCHTYPEM (int /*<<< orphan*/ ) ; 
 int V_FW_FILTER_WR_NOREPLY (int /*<<< orphan*/ ) ; 
 int V_FW_FILTER_WR_OVLAN_VLD (int) ; 
 int V_FW_FILTER_WR_OVLAN_VLDM (int) ; 
 int V_FW_FILTER_WR_PORT (int /*<<< orphan*/ ) ; 
 int V_FW_FILTER_WR_PORTM (int /*<<< orphan*/ ) ; 
 int V_FW_FILTER_WR_PRIO (scalar_t__) ; 
 int V_FW_FILTER_WR_RMVLAN (int) ; 
 int V_FW_FILTER_WR_RPTTID (int /*<<< orphan*/ ) ; 
 int V_FW_FILTER_WR_RQTYPE (scalar_t__) ; 
 int V_FW_FILTER_WR_RX_CHAN (int /*<<< orphan*/ ) ; 
 int V_FW_FILTER_WR_RX_RPL_IQ (int /*<<< orphan*/ ) ; 
 int V_FW_FILTER_WR_SMAC (int /*<<< orphan*/ ) ; 
 int V_FW_FILTER_WR_TID (int) ; 
 int V_FW_FILTER_WR_TXCHAN (int /*<<< orphan*/ ) ; 
 int V_FW_WR_OP (int /*<<< orphan*/ ) ; 
 scalar_t__ __predict_false (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bzero (struct fw_filter2_wr*,int) ; 
 int /*<<< orphan*/  commit_wrq_wr (int /*<<< orphan*/ *,struct fw_filter2_wr*,struct wrq_cookie*) ; 
 scalar_t__ cv_wait_sig (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int howmany (int,int) ; 
 void* htobe16 (int) ; 
 void* htobe32 (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ separate_hpfilter_region (struct adapter*) ; 
 struct fw_filter2_wr* start_wrq_wr (int /*<<< orphan*/ *,int,struct wrq_cookie*) ; 

__attribute__((used)) static int
set_tcamfilter(struct adapter *sc, struct t4_filter *t, struct l2t_entry *l2te,
    struct smt_entry *smt)
{
	struct filter_entry *f;
	struct fw_filter2_wr *fwr;
	u_int vnic_vld, vnic_vld_mask;
	struct wrq_cookie cookie;
	int i, rc, busy, locked;
	u_int tid;
	const int ntids = t->fs.type ? 4 : 1;

	MPASS(!t->fs.hash);
	/* Already validated against fconf, iconf */
	MPASS((t->fs.val.pfvf_vld & t->fs.val.ovlan_vld) == 0);
	MPASS((t->fs.mask.pfvf_vld & t->fs.mask.ovlan_vld) == 0);

	if (separate_hpfilter_region(sc) && t->fs.prio) {
		MPASS(t->idx < sc->tids.nhpftids);
		f = &sc->tids.hpftid_tab[t->idx];
		tid = sc->tids.hpftid_base + t->idx;
	} else {
		MPASS(t->idx < sc->tids.nftids);
		f = &sc->tids.ftid_tab[t->idx];
		tid = sc->tids.ftid_base + t->idx;
	}
	rc = busy = locked = 0;
	mtx_lock(&sc->tids.ftid_lock);
	for (i = 0; i < ntids; i++) {
		busy += f[i].pending + f[i].valid;
		locked += f[i].locked;
	}
	if (locked > 0)
		rc = EPERM;
	else if (busy > 0)
		rc = EBUSY;
	else {
		int len16;

		if (sc->params.filter2_wr_support)
			len16 = howmany(sizeof(struct fw_filter2_wr), 16);
		else
			len16 = howmany(sizeof(struct fw_filter_wr), 16);
		fwr = start_wrq_wr(&sc->sge.ctrlq[0], len16, &cookie);
		if (__predict_false(fwr == NULL))
			rc = ENOMEM;
		else {
			f->pending = 1;
			if (separate_hpfilter_region(sc) && t->fs.prio)
				sc->tids.hpftids_in_use++;
			else
				sc->tids.ftids_in_use++;
		}
	}
	mtx_unlock(&sc->tids.ftid_lock);
	if (rc != 0)
		return (rc);

	/*
	 * Can't fail now.  A set-filter WR will definitely be sent.
	 */

	f->tid = tid;
	f->fs = t->fs;
	f->l2te = l2te;
	f->smt = smt;

	if (t->fs.val.pfvf_vld || t->fs.val.ovlan_vld)
		vnic_vld = 1;
	else
		vnic_vld = 0;
	if (t->fs.mask.pfvf_vld || t->fs.mask.ovlan_vld)
		vnic_vld_mask = 1;
	else
		vnic_vld_mask = 0;

	bzero(fwr, sizeof(*fwr));
	if (sc->params.filter2_wr_support)
		fwr->op_pkd = htobe32(V_FW_WR_OP(FW_FILTER2_WR));
	else
		fwr->op_pkd = htobe32(V_FW_WR_OP(FW_FILTER_WR));
	fwr->len16_pkd = htobe32(FW_LEN16(*fwr));
	fwr->tid_to_iq =
	    htobe32(V_FW_FILTER_WR_TID(f->tid) |
		V_FW_FILTER_WR_RQTYPE(f->fs.type) |
		V_FW_FILTER_WR_NOREPLY(0) |
		V_FW_FILTER_WR_IQ(f->fs.iq));
	fwr->del_filter_to_l2tix =
	    htobe32(V_FW_FILTER_WR_RPTTID(f->fs.rpttid) |
		V_FW_FILTER_WR_DROP(f->fs.action == FILTER_DROP) |
		V_FW_FILTER_WR_DIRSTEER(f->fs.dirsteer) |
		V_FW_FILTER_WR_MASKHASH(f->fs.maskhash) |
		V_FW_FILTER_WR_DIRSTEERHASH(f->fs.dirsteerhash) |
		V_FW_FILTER_WR_LPBK(f->fs.action == FILTER_SWITCH) |
		V_FW_FILTER_WR_DMAC(f->fs.newdmac) |
		V_FW_FILTER_WR_SMAC(f->fs.newsmac) |
		V_FW_FILTER_WR_INSVLAN(f->fs.newvlan == VLAN_INSERT ||
		    f->fs.newvlan == VLAN_REWRITE) |
		V_FW_FILTER_WR_RMVLAN(f->fs.newvlan == VLAN_REMOVE ||
		    f->fs.newvlan == VLAN_REWRITE) |
		V_FW_FILTER_WR_HITCNTS(f->fs.hitcnts) |
		V_FW_FILTER_WR_TXCHAN(f->fs.eport) |
		V_FW_FILTER_WR_PRIO(f->fs.prio) |
		V_FW_FILTER_WR_L2TIX(f->l2te ? f->l2te->idx : 0));
	fwr->ethtype = htobe16(f->fs.val.ethtype);
	fwr->ethtypem = htobe16(f->fs.mask.ethtype);
	fwr->frag_to_ovlan_vldm =
	    (V_FW_FILTER_WR_FRAG(f->fs.val.frag) |
		V_FW_FILTER_WR_FRAGM(f->fs.mask.frag) |
		V_FW_FILTER_WR_IVLAN_VLD(f->fs.val.vlan_vld) |
		V_FW_FILTER_WR_OVLAN_VLD(vnic_vld) |
		V_FW_FILTER_WR_IVLAN_VLDM(f->fs.mask.vlan_vld) |
		V_FW_FILTER_WR_OVLAN_VLDM(vnic_vld_mask));
	fwr->smac_sel = 0;
	fwr->rx_chan_rx_rpl_iq = htobe16(V_FW_FILTER_WR_RX_CHAN(0) |
	    V_FW_FILTER_WR_RX_RPL_IQ(sc->sge.fwq.abs_id));
	fwr->maci_to_matchtypem =
	    htobe32(V_FW_FILTER_WR_MACI(f->fs.val.macidx) |
		V_FW_FILTER_WR_MACIM(f->fs.mask.macidx) |
		V_FW_FILTER_WR_FCOE(f->fs.val.fcoe) |
		V_FW_FILTER_WR_FCOEM(f->fs.mask.fcoe) |
		V_FW_FILTER_WR_PORT(f->fs.val.iport) |
		V_FW_FILTER_WR_PORTM(f->fs.mask.iport) |
		V_FW_FILTER_WR_MATCHTYPE(f->fs.val.matchtype) |
		V_FW_FILTER_WR_MATCHTYPEM(f->fs.mask.matchtype));
	fwr->ptcl = f->fs.val.proto;
	fwr->ptclm = f->fs.mask.proto;
	fwr->ttyp = f->fs.val.tos;
	fwr->ttypm = f->fs.mask.tos;
	fwr->ivlan = htobe16(f->fs.val.vlan);
	fwr->ivlanm = htobe16(f->fs.mask.vlan);
	fwr->ovlan = htobe16(f->fs.val.vnic);
	fwr->ovlanm = htobe16(f->fs.mask.vnic);
	bcopy(f->fs.val.dip, fwr->lip, sizeof (fwr->lip));
	bcopy(f->fs.mask.dip, fwr->lipm, sizeof (fwr->lipm));
	bcopy(f->fs.val.sip, fwr->fip, sizeof (fwr->fip));
	bcopy(f->fs.mask.sip, fwr->fipm, sizeof (fwr->fipm));
	fwr->lp = htobe16(f->fs.val.dport);
	fwr->lpm = htobe16(f->fs.mask.dport);
	fwr->fp = htobe16(f->fs.val.sport);
	fwr->fpm = htobe16(f->fs.mask.sport);
	/* sma = 0 tells the fw to use SMAC_SEL for source MAC address */
	bzero(fwr->sma, sizeof (fwr->sma));
	if (sc->params.filter2_wr_support) {
		fwr->filter_type_swapmac =
		    V_FW_FILTER2_WR_SWAPMAC(f->fs.swapmac);
		fwr->natmode_to_ulp_type =
		    V_FW_FILTER2_WR_ULP_TYPE(f->fs.nat_mode ?
			ULP_MODE_TCPDDP : ULP_MODE_NONE) |
		    V_FW_FILTER2_WR_NATFLAGCHECK(f->fs.nat_flag_chk) |
		    V_FW_FILTER2_WR_NATMODE(f->fs.nat_mode);
		memcpy(fwr->newlip, f->fs.nat_dip, sizeof(fwr->newlip));
		memcpy(fwr->newfip, f->fs.nat_sip, sizeof(fwr->newfip));
		fwr->newlport = htobe16(f->fs.nat_dport);
		fwr->newfport = htobe16(f->fs.nat_sport);
		fwr->natseqcheck = htobe32(f->fs.nat_seq_chk);
	}
	commit_wrq_wr(&sc->sge.ctrlq[0], fwr, &cookie);

	/* Wait for response. */
	mtx_lock(&sc->tids.ftid_lock);
	for (;;) {
		if (f->pending == 0) {
			rc = f->valid ? 0 : EIO;
			break;
		}
		if (cv_wait_sig(&sc->tids.ftid_cv, &sc->tids.ftid_lock) != 0) {
			rc = EINPROGRESS;
			break;
		}
	}
	mtx_unlock(&sc->tids.ftid_lock);
	return (rc);
}