#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct qlnxr_dev {TYPE_3__* ha; int /*<<< orphan*/  gsi_ll2_handle; int /*<<< orphan*/  rdma_ctx; } ;
struct TYPE_5__ {int /*<<< orphan*/  len; int /*<<< orphan*/  baddr; int /*<<< orphan*/  vaddr; } ;
struct ecore_roce_ll2_packet {scalar_t__ roce_mode; int n_seg; TYPE_2__* payload; TYPE_1__ header; } ;
struct ecore_ll2_tx_pkt_info {int num_of_bds; int ecore_roce_flavor; int enable_ip_cksum; struct ecore_roce_ll2_packet* cookie; int /*<<< orphan*/  first_frag_len; int /*<<< orphan*/  first_frag; int /*<<< orphan*/  tx_dest; scalar_t__ vlan; } ;
struct ecore_ll2_stats {int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  ll2_tx_pkt ;
typedef  enum ecore_ll2_roce_flavor_type { ____Placeholder_ecore_ll2_roce_flavor_type } ecore_ll2_roce_flavor_type ;
struct TYPE_7__ {int /*<<< orphan*/  cdev; } ;
struct TYPE_6__ {int /*<<< orphan*/  len; int /*<<< orphan*/  baddr; } ;

/* Variables and functions */
 int ECORE_LL2_ROCE ; 
 int ECORE_LL2_RROCE ; 
 int /*<<< orphan*/  ECORE_LL2_TX_DEST_NW ; 
 int /*<<< orphan*/  QL_DPRINT11 (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  QL_DPRINT12 (TYPE_3__*,char*) ; 
 scalar_t__ ROCE_V1 ; 
 int ecore_ll2_get_stats (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ecore_ll2_stats*) ; 
 int ecore_ll2_prepare_tx_packet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ecore_ll2_tx_pkt_info*,int) ; 
 int ecore_ll2_set_fragment_of_tx_packet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ecore_roce_ll2_packet*) ; 
 int /*<<< orphan*/  memset (struct ecore_ll2_tx_pkt_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qlnx_dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
qlnxr_ll2_post_tx(struct qlnxr_dev *dev, struct ecore_roce_ll2_packet *pkt)
{
	enum ecore_ll2_roce_flavor_type roce_flavor;
	struct ecore_ll2_tx_pkt_info ll2_tx_pkt;
	int rc;
	int i;

	QL_DPRINT12(dev->ha, "enter\n");

	memset(&ll2_tx_pkt, 0, sizeof(ll2_tx_pkt));

	if (pkt->roce_mode != ROCE_V1) {
		QL_DPRINT11(dev->ha, "roce_mode != ROCE_V1\n");
		return (-1);
	}

	roce_flavor = (pkt->roce_mode == ROCE_V1) ?
		ECORE_LL2_ROCE : ECORE_LL2_RROCE;

	ll2_tx_pkt.num_of_bds = 1 /* hdr */ +  pkt->n_seg;
	ll2_tx_pkt.vlan = 0; /* ??? */
	ll2_tx_pkt.tx_dest = ECORE_LL2_TX_DEST_NW;
	ll2_tx_pkt.ecore_roce_flavor = roce_flavor;
	ll2_tx_pkt.first_frag = pkt->header.baddr;
	ll2_tx_pkt.first_frag_len = pkt->header.len;
	ll2_tx_pkt.cookie = pkt;
	ll2_tx_pkt.enable_ip_cksum = 1; // Only for RoCEv2:IPv4

	/* tx header */
	rc = ecore_ll2_prepare_tx_packet(dev->rdma_ctx,
			dev->gsi_ll2_handle,
			&ll2_tx_pkt,
			1);
	if (rc) {

		QL_DPRINT11(dev->ha, "ecore_ll2_prepare_tx_packet failed\n");

		/* TX failed while posting header - release resources*/
                qlnx_dma_free_coherent(&dev->ha->cdev,
			pkt->header.vaddr,
			pkt->header.baddr,
                        pkt->header.len);

		kfree(pkt);

		return rc;
	}

	/* tx payload */
	for (i = 0; i < pkt->n_seg; i++) {
		rc = ecore_ll2_set_fragment_of_tx_packet(dev->rdma_ctx,
						       dev->gsi_ll2_handle,
						       pkt->payload[i].baddr,
						       pkt->payload[i].len);
		if (rc) {
			/* if failed not much to do here, partial packet has
			 * been posted we can't free memory, will need to wait
			 * for completion
			 */
			QL_DPRINT11(dev->ha,
				"ecore_ll2_set_fragment_of_tx_packet failed\n");
			return rc;
		}
	}
	struct ecore_ll2_stats stats = {0};
	rc = ecore_ll2_get_stats(dev->rdma_ctx, dev->gsi_ll2_handle, &stats);
	if (rc) {
		QL_DPRINT11(dev->ha, "failed to obtain ll2 stats\n");
	}
	QL_DPRINT12(dev->ha, "exit\n");

	return 0;
}