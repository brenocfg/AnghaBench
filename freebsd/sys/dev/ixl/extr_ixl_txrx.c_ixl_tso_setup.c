#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  scalar_t__ u32 ;
struct tx_ring {TYPE_2__* que; int /*<<< orphan*/  mss_too_small; int /*<<< orphan*/ * tx_base; } ;
struct i40e_tx_context_desc {int /*<<< orphan*/  tunneling_params; int /*<<< orphan*/  type_cmd_tso_mss; } ;
typedef  TYPE_3__* if_softc_ctx_t ;
typedef  TYPE_4__* if_pkt_info_t ;
struct TYPE_9__ {int ipi_pidx; int ipi_ehdrlen; int ipi_ip_hlen; int ipi_tcp_hlen; scalar_t__ ipi_len; scalar_t__ ipi_tso_segsz; } ;
struct TYPE_8__ {int* isc_ntxd; } ;
struct TYPE_7__ {int /*<<< orphan*/  tso; TYPE_1__* vsi; } ;
struct TYPE_6__ {TYPE_3__* shared; } ;

/* Variables and functions */
 int I40E_TXD_CTX_QW1_CMD_SHIFT ; 
 int I40E_TXD_CTX_QW1_DTYPE_SHIFT ; 
 int I40E_TXD_CTX_QW1_MSS_SHIFT ; 
 int I40E_TXD_CTX_QW1_TSO_LEN_SHIFT ; 
 scalar_t__ I40E_TX_CTX_DESC_TSO ; 
 scalar_t__ I40E_TX_DESC_DTYPE_CONTEXT ; 
 scalar_t__ IXL_MAX_FRAME ; 
 scalar_t__ IXL_MAX_TSO_MSS ; 
 scalar_t__ IXL_MIN_TSO_MSS ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  htole32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htole64 (int) ; 

__attribute__((used)) static int
ixl_tso_setup(struct tx_ring *txr, if_pkt_info_t pi)
{
	if_softc_ctx_t			scctx;
	struct i40e_tx_context_desc	*TXD;
	u32				cmd, mss, type, tsolen;
	int				idx, total_hdr_len;
	u64				type_cmd_tso_mss;

	idx = pi->ipi_pidx;
	TXD = (struct i40e_tx_context_desc *) &txr->tx_base[idx];
	total_hdr_len = pi->ipi_ehdrlen + pi->ipi_ip_hlen + pi->ipi_tcp_hlen;
	tsolen = pi->ipi_len - total_hdr_len;
	scctx = txr->que->vsi->shared;

	type = I40E_TX_DESC_DTYPE_CONTEXT;
	cmd = I40E_TX_CTX_DESC_TSO;
	/*
	 * TSO MSS must not be less than 64; this prevents a
	 * BAD_LSO_MSS MDD event when the MSS is too small.
	 */
	if (pi->ipi_tso_segsz < IXL_MIN_TSO_MSS) {
		txr->mss_too_small++;
		pi->ipi_tso_segsz = IXL_MIN_TSO_MSS;
	}
	mss = pi->ipi_tso_segsz;

	/* Check for BAD_LS0_MSS MDD event (mss too large) */
	MPASS(mss <= IXL_MAX_TSO_MSS);
	/* Check for NO_HEAD MDD event (header lengths are 0) */
	MPASS(pi->ipi_ehdrlen != 0);
	MPASS(pi->ipi_ip_hlen != 0);
	/* Partial check for BAD_LSO_LEN MDD event */
	MPASS(tsolen != 0);
	/* Partial check for WRONG_SIZE MDD event (during TSO) */
	MPASS(total_hdr_len + mss <= IXL_MAX_FRAME);

	type_cmd_tso_mss = ((u64)type << I40E_TXD_CTX_QW1_DTYPE_SHIFT) |
	    ((u64)cmd << I40E_TXD_CTX_QW1_CMD_SHIFT) |
	    ((u64)tsolen << I40E_TXD_CTX_QW1_TSO_LEN_SHIFT) |
	    ((u64)mss << I40E_TXD_CTX_QW1_MSS_SHIFT);
	TXD->type_cmd_tso_mss = htole64(type_cmd_tso_mss);

	TXD->tunneling_params = htole32(0);
	txr->que->tso++;

	return ((idx + 1) & (scctx->isc_ntxd[0]-1));
}