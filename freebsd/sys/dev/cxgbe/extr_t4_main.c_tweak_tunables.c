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

/* Variables and functions */
 scalar_t__ CPU_VENDOR_INTEL ; 
 int FW_CAPS_CONFIG_ISCSI_INITIATOR_PDU ; 
 int FW_CAPS_CONFIG_ISCSI_T10DIF ; 
 int FW_CAPS_CONFIG_ISCSI_TARGET_PDU ; 
 int FW_CAPS_CONFIG_RDMA_RDDP ; 
 int FW_CAPS_CONFIG_RDMA_RDMAC ; 
 int FW_CAPS_CONFIG_TOE ; 
 int INTR_INTX ; 
 int INTR_MSI ; 
 int INTR_MSIX ; 
 int /*<<< orphan*/  NNMRXQ_VI ; 
 int /*<<< orphan*/  NNMTXQ_VI ; 
 int /*<<< orphan*/  NOFLDRXQ ; 
 int /*<<< orphan*/  NOFLDRXQ_VI ; 
 int /*<<< orphan*/  NOFLDTXQ ; 
 int /*<<< orphan*/  NOFLDTXQ_VI ; 
 int /*<<< orphan*/  NRXQ ; 
 int /*<<< orphan*/  NRXQ_VI ; 
 int /*<<< orphan*/  NTXQ ; 
 int /*<<< orphan*/  NTXQ_VI ; 
 int PKTC_IDX ; 
 int PKTC_IDX_OFLD ; 
 int SGE_NCOUNTERS ; 
 scalar_t__ SGE_NTIMERS ; 
 scalar_t__ TMR_IDX ; 
 scalar_t__ TMR_IDX_OFLD ; 
 int /*<<< orphan*/  calculate_nqueues (int*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_vendor_id ; 
 int mp_ncpus ; 
 int nitems (int /*<<< orphan*/ ) ; 
 int pcie_relaxed_ordering ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int rss_getnumbuckets () ; 
 int t4_intr_types ; 
 int t4_iscsicaps_allowed ; 
 int t4_nnmrxq_vi ; 
 int t4_nnmtxq_vi ; 
 int t4_nofldrxq ; 
 int t4_nofldrxq_vi ; 
 int t4_nofldtxq ; 
 int t4_nofldtxq_vi ; 
 int t4_nrxq ; 
 int t4_nrxq_vi ; 
 int t4_ntxq ; 
 int t4_ntxq_vi ; 
 int t4_num_vis ; 
 int t4_pktc_idx ; 
 int t4_pktc_idx_ofld ; 
 int t4_qsize_rxq ; 
 int t4_qsize_txq ; 
 int t4_rdmacaps_allowed ; 
 scalar_t__ t4_tmr_idx ; 
 scalar_t__ t4_tmr_idx_ofld ; 
 int t4_toecaps_allowed ; 
 int /*<<< orphan*/  vi_mac_funcs ; 

__attribute__((used)) static void
tweak_tunables(void)
{
	int nc = mp_ncpus;	/* our snapshot of the number of CPUs */

	if (t4_ntxq < 1) {
#ifdef RSS
		t4_ntxq = rss_getnumbuckets();
#else
		calculate_nqueues(&t4_ntxq, nc, NTXQ);
#endif
	}

	calculate_nqueues(&t4_ntxq_vi, nc, NTXQ_VI);

	if (t4_nrxq < 1) {
#ifdef RSS
		t4_nrxq = rss_getnumbuckets();
#else
		calculate_nqueues(&t4_nrxq, nc, NRXQ);
#endif
	}

	calculate_nqueues(&t4_nrxq_vi, nc, NRXQ_VI);

#if defined(TCP_OFFLOAD) || defined(RATELIMIT)
	calculate_nqueues(&t4_nofldtxq, nc, NOFLDTXQ);
	calculate_nqueues(&t4_nofldtxq_vi, nc, NOFLDTXQ_VI);
#endif
#ifdef TCP_OFFLOAD
	calculate_nqueues(&t4_nofldrxq, nc, NOFLDRXQ);
	calculate_nqueues(&t4_nofldrxq_vi, nc, NOFLDRXQ_VI);

	if (t4_toecaps_allowed == -1)
		t4_toecaps_allowed = FW_CAPS_CONFIG_TOE;

	if (t4_rdmacaps_allowed == -1) {
		t4_rdmacaps_allowed = FW_CAPS_CONFIG_RDMA_RDDP |
		    FW_CAPS_CONFIG_RDMA_RDMAC;
	}

	if (t4_iscsicaps_allowed == -1) {
		t4_iscsicaps_allowed = FW_CAPS_CONFIG_ISCSI_INITIATOR_PDU |
		    FW_CAPS_CONFIG_ISCSI_TARGET_PDU |
		    FW_CAPS_CONFIG_ISCSI_T10DIF;
	}

	if (t4_tmr_idx_ofld < 0 || t4_tmr_idx_ofld >= SGE_NTIMERS)
		t4_tmr_idx_ofld = TMR_IDX_OFLD;

	if (t4_pktc_idx_ofld < -1 || t4_pktc_idx_ofld >= SGE_NCOUNTERS)
		t4_pktc_idx_ofld = PKTC_IDX_OFLD;
#else
	if (t4_toecaps_allowed == -1)
		t4_toecaps_allowed = 0;

	if (t4_rdmacaps_allowed == -1)
		t4_rdmacaps_allowed = 0;

	if (t4_iscsicaps_allowed == -1)
		t4_iscsicaps_allowed = 0;
#endif

#ifdef DEV_NETMAP
	calculate_nqueues(&t4_nnmtxq_vi, nc, NNMTXQ_VI);
	calculate_nqueues(&t4_nnmrxq_vi, nc, NNMRXQ_VI);
#endif

	if (t4_tmr_idx < 0 || t4_tmr_idx >= SGE_NTIMERS)
		t4_tmr_idx = TMR_IDX;

	if (t4_pktc_idx < -1 || t4_pktc_idx >= SGE_NCOUNTERS)
		t4_pktc_idx = PKTC_IDX;

	if (t4_qsize_txq < 128)
		t4_qsize_txq = 128;

	if (t4_qsize_rxq < 128)
		t4_qsize_rxq = 128;
	while (t4_qsize_rxq & 7)
		t4_qsize_rxq++;

	t4_intr_types &= INTR_MSIX | INTR_MSI | INTR_INTX;

	/*
	 * Number of VIs to create per-port.  The first VI is the "main" regular
	 * VI for the port.  The rest are additional virtual interfaces on the
	 * same physical port.  Note that the main VI does not have native
	 * netmap support but the extra VIs do.
	 *
	 * Limit the number of VIs per port to the number of available
	 * MAC addresses per port.
	 */
	if (t4_num_vis < 1)
		t4_num_vis = 1;
	if (t4_num_vis > nitems(vi_mac_funcs)) {
		t4_num_vis = nitems(vi_mac_funcs);
		printf("cxgbe: number of VIs limited to %d\n", t4_num_vis);
	}

	if (pcie_relaxed_ordering < 0 || pcie_relaxed_ordering > 2) {
		pcie_relaxed_ordering = 1;
#if defined(__i386__) || defined(__amd64__)
		if (cpu_vendor_id == CPU_VENDOR_INTEL)
			pcie_relaxed_ordering = 0;
#endif
	}
}