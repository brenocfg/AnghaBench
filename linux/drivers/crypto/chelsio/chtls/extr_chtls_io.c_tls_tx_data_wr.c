#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct tls_scmd {int seqno_numivs; int ivgen_hdrlen; } ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
struct fw_tlstx_data_wr {scalar_t__ r10; int /*<<< orphan*/  pdusinplenmax_pkd; void* expinplenmax_pkd; void* adjustedplen_pkd; void* mfs; void* plen; void* ctxloc_to_exp; void* lsodisable_to_flags; void* flowid_len16; void* op_to_immdlen; } ;
struct cpl_tx_tls_sfo {int /*<<< orphan*/  scmd1; void* ivgen_hdrlen; void* seqno_numivs; scalar_t__ r1_lo; void* type_protover; void* pld_len; void* op_to_seg_len; } ;
struct chtls_hws {int mfs; int keylen; struct tls_scmd scmd; int /*<<< orphan*/  pdus; int /*<<< orphan*/  expansion; int /*<<< orphan*/  adjustlen; } ;
struct chtls_sock {int /*<<< orphan*/  txq; int /*<<< orphan*/  tid; struct chtls_hws tlshws; struct net_device* egress_dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  tls_pdu_tx; } ;
struct adapter {TYPE_1__ chcr_stats; } ;
struct TYPE_7__ {int /*<<< orphan*/  type; } ;
struct TYPE_8__ {TYPE_2__ tls; } ;
struct TYPE_10__ {TYPE_3__ ulp; } ;
struct TYPE_9__ {int nonagle; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHTLS_KEY_CONTEXT_DDR ; 
 int /*<<< orphan*/  CPL_TX_TLS_SFO ; 
 int CPL_TX_TLS_SFO_CPL_LEN_V (int) ; 
 int CPL_TX_TLS_SFO_DATA_TYPE_V (unsigned char) ; 
 int CPL_TX_TLS_SFO_OPCODE_V (int /*<<< orphan*/ ) ; 
 int CPL_TX_TLS_SFO_PROTOVER_V (int /*<<< orphan*/ ) ; 
 int CPL_TX_TLS_SFO_SEG_LEN_V (int) ; 
 unsigned char CPL_TX_TLS_SFO_TYPE_HEARTBEAT ; 
 int CPL_TX_TLS_SFO_TYPE_V (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSK_TX_MORE_DATA ; 
 unsigned int FW_OFLD_TX_DATA_WR_ALIGNPLD_F ; 
 unsigned int FW_OFLD_TX_DATA_WR_SHOVE_F ; 
 int /*<<< orphan*/  FW_TLSTX_DATA_WR ; 
 int FW_TLSTX_DATA_WR_ADJUSTEDPLEN_V (int /*<<< orphan*/ ) ; 
 int FW_TLSTX_DATA_WR_COMPL_V (int) ; 
 int FW_TLSTX_DATA_WR_CTXLOC_V (int /*<<< orphan*/ ) ; 
 int FW_TLSTX_DATA_WR_EXPINPLENMAX_V (int /*<<< orphan*/ ) ; 
 int FW_TLSTX_DATA_WR_EXP_V (int) ; 
 int FW_TLSTX_DATA_WR_FLOWID_V (int /*<<< orphan*/ ) ; 
 int FW_TLSTX_DATA_WR_IMMDLEN_V (int) ; 
 int FW_TLSTX_DATA_WR_IVDSGL_V (int) ; 
 int FW_TLSTX_DATA_WR_KEYSIZE_V (int) ; 
 int FW_TLSTX_DATA_WR_LEN16_V (int /*<<< orphan*/ ) ; 
 int FW_TLSTX_DATA_WR_NUMIVS_V (int) ; 
 int /*<<< orphan*/  FW_TLSTX_DATA_WR_PDUSINPLENMAX_V (int /*<<< orphan*/ ) ; 
 int FW_WR_OP_V (int /*<<< orphan*/ ) ; 
 int SCMD_NUM_IVS_V (int) ; 
 unsigned int T6_TX_FORCE_F ; 
 int TCP_NAGLE_OFF ; 
 int /*<<< orphan*/  TLS_HDR_TYPE_HEARTBEAT ; 
 unsigned int TX_SHOVE_V (int) ; 
 unsigned int TX_ULP_MODE_V (int /*<<< orphan*/ ) ; 
 unsigned int TX_URG_V (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ULP_MODE_TLS ; 
 TYPE_5__* ULP_SKB_CB (struct sk_buff*) ; 
 scalar_t__ __skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csk_flag (struct sock*,int /*<<< orphan*/ ) ; 
 void* htonl (int) ; 
 void* htons (int) ; 
 scalar_t__ is_sg_request (struct sk_buff*) ; 
 struct adapter* netdev2adap (struct net_device*) ; 
 struct chtls_sock* rcu_dereference_sk_user_data (struct sock*) ; 
 scalar_t__ skb_queue_empty (int /*<<< orphan*/ *) ; 
 int skb_ulp_tls_iv_imm (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_urgent (struct sk_buff*) ; 
 TYPE_4__* tcp_sk (struct sock*) ; 
 unsigned char tls_content_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tlstx_incr_seqnum (struct chtls_hws*) ; 

__attribute__((used)) static void tls_tx_data_wr(struct sock *sk, struct sk_buff *skb,
			   int dlen, int tls_immd, u32 credits,
			   int expn, int pdus)
{
	struct fw_tlstx_data_wr *req_wr;
	struct cpl_tx_tls_sfo *req_cpl;
	unsigned int wr_ulp_mode_force;
	struct tls_scmd *updated_scmd;
	unsigned char data_type;
	struct chtls_sock *csk;
	struct net_device *dev;
	struct chtls_hws *hws;
	struct tls_scmd *scmd;
	struct adapter *adap;
	unsigned char *req;
	int immd_len;
	int iv_imm;
	int len;

	csk = rcu_dereference_sk_user_data(sk);
	iv_imm = skb_ulp_tls_iv_imm(skb);
	dev = csk->egress_dev;
	adap = netdev2adap(dev);
	hws = &csk->tlshws;
	scmd = &hws->scmd;
	len = dlen + expn;

	dlen = (dlen < hws->mfs) ? dlen : hws->mfs;
	atomic_inc(&adap->chcr_stats.tls_pdu_tx);

	updated_scmd = scmd;
	updated_scmd->seqno_numivs &= 0xffffff80;
	updated_scmd->seqno_numivs |= SCMD_NUM_IVS_V(pdus);
	hws->scmd = *updated_scmd;

	req = (unsigned char *)__skb_push(skb, sizeof(struct cpl_tx_tls_sfo));
	req_cpl = (struct cpl_tx_tls_sfo *)req;
	req = (unsigned char *)__skb_push(skb, (sizeof(struct
				fw_tlstx_data_wr)));

	req_wr = (struct fw_tlstx_data_wr *)req;
	immd_len = (tls_immd ? dlen : 0);
	req_wr->op_to_immdlen =
		htonl(FW_WR_OP_V(FW_TLSTX_DATA_WR) |
		FW_TLSTX_DATA_WR_COMPL_V(1) |
		FW_TLSTX_DATA_WR_IMMDLEN_V(immd_len));
	req_wr->flowid_len16 = htonl(FW_TLSTX_DATA_WR_FLOWID_V(csk->tid) |
				     FW_TLSTX_DATA_WR_LEN16_V(credits));
	wr_ulp_mode_force = TX_ULP_MODE_V(ULP_MODE_TLS);

	if (is_sg_request(skb))
		wr_ulp_mode_force |= FW_OFLD_TX_DATA_WR_ALIGNPLD_F |
			((tcp_sk(sk)->nonagle & TCP_NAGLE_OFF) ? 0 :
			FW_OFLD_TX_DATA_WR_SHOVE_F);

	req_wr->lsodisable_to_flags =
			htonl(TX_ULP_MODE_V(ULP_MODE_TLS) |
			      TX_URG_V(skb_urgent(skb)) |
			      T6_TX_FORCE_F | wr_ulp_mode_force |
			      TX_SHOVE_V((!csk_flag(sk, CSK_TX_MORE_DATA)) &&
					 skb_queue_empty(&csk->txq)));

	req_wr->ctxloc_to_exp =
			htonl(FW_TLSTX_DATA_WR_NUMIVS_V(pdus) |
			      FW_TLSTX_DATA_WR_EXP_V(expn) |
			      FW_TLSTX_DATA_WR_CTXLOC_V(CHTLS_KEY_CONTEXT_DDR) |
			      FW_TLSTX_DATA_WR_IVDSGL_V(!iv_imm) |
			      FW_TLSTX_DATA_WR_KEYSIZE_V(hws->keylen >> 4));

	/* Fill in the length */
	req_wr->plen = htonl(len);
	req_wr->mfs = htons(hws->mfs);
	req_wr->adjustedplen_pkd =
		htons(FW_TLSTX_DATA_WR_ADJUSTEDPLEN_V(hws->adjustlen));
	req_wr->expinplenmax_pkd =
		htons(FW_TLSTX_DATA_WR_EXPINPLENMAX_V(hws->expansion));
	req_wr->pdusinplenmax_pkd =
		FW_TLSTX_DATA_WR_PDUSINPLENMAX_V(hws->pdus);
	req_wr->r10 = 0;

	data_type = tls_content_type(ULP_SKB_CB(skb)->ulp.tls.type);
	req_cpl->op_to_seg_len = htonl(CPL_TX_TLS_SFO_OPCODE_V(CPL_TX_TLS_SFO) |
				       CPL_TX_TLS_SFO_DATA_TYPE_V(data_type) |
				       CPL_TX_TLS_SFO_CPL_LEN_V(2) |
				       CPL_TX_TLS_SFO_SEG_LEN_V(dlen));
	req_cpl->pld_len = htonl(len - expn);

	req_cpl->type_protover = htonl(CPL_TX_TLS_SFO_TYPE_V
		((data_type == CPL_TX_TLS_SFO_TYPE_HEARTBEAT) ?
		TLS_HDR_TYPE_HEARTBEAT : 0) |
		CPL_TX_TLS_SFO_PROTOVER_V(0));

	/* create the s-command */
	req_cpl->r1_lo = 0;
	req_cpl->seqno_numivs  = cpu_to_be32(hws->scmd.seqno_numivs);
	req_cpl->ivgen_hdrlen = cpu_to_be32(hws->scmd.ivgen_hdrlen);
	req_cpl->scmd1 = cpu_to_be64(tlstx_incr_seqnum(hws));
}