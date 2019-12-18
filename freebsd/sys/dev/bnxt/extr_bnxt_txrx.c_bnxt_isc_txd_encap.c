#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int uint16_t ;
struct tx_bd_long_hi {void* lflags; int /*<<< orphan*/  cfa_meta; scalar_t__ cfa_action; void* hdr_size; void* mss; } ;
struct tx_bd_long {int opaque; void* flags_type; void* addr; void* len; } ;
struct bnxt_softc {struct bnxt_ring* tx_rings; } ;
struct bnxt_ring {scalar_t__ vaddr; } ;
typedef  TYPE_2__* if_pkt_info_t ;
struct TYPE_5__ {size_t ipi_qsidx; int ipi_csum_flags; int ipi_mflags; size_t ipi_new_pidx; size_t ipi_pidx; int ipi_nsegs; int ipi_len; int ipi_tso_segsz; int ipi_ehdrlen; int ipi_ip_hlen; int ipi_tcp_hlen; int ipi_vtag; TYPE_1__* ipi_segs; scalar_t__ ipi_ndescs; } ;
struct TYPE_4__ {int ds_len; int /*<<< orphan*/  ds_addr; } ;

/* Variables and functions */
 int CSUM_IP ; 
 int CSUM_OFFLOAD ; 
 int CSUM_TSO ; 
 int M_VLANTAG ; 
 void* RING_NEXT (struct bnxt_ring*,int) ; 
 int TX_BD_LONG_CFA_META_KEY_VLAN_TAG ; 
 int TX_BD_LONG_CFA_META_VLAN_TPID_TPID8100 ; 
 int TX_BD_LONG_LFLAGS_IP_CHKSUM ; 
 int TX_BD_LONG_LFLAGS_LSO ; 
 int TX_BD_LONG_LFLAGS_TCP_UDP_CHKSUM ; 
 int TX_BD_LONG_LFLAGS_T_IPID ; 
 int TX_BD_LONG_TYPE_TX_BD_LONG ; 
 int TX_BD_SHORT_FLAGS_BD_CNT_MASK ; 
 int TX_BD_SHORT_FLAGS_BD_CNT_SFT ; 
 int TX_BD_SHORT_FLAGS_LHINT_GTE2K ; 
 int TX_BD_SHORT_FLAGS_PACKET_END ; 
 int TX_BD_SHORT_TYPE_TX_BD_SHORT ; 
 int* bnxt_tx_lhint ; 
 void* htole16 (int) ; 
 int /*<<< orphan*/  htole32 (int) ; 
 void* htole64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bnxt_isc_txd_encap(void *sc, if_pkt_info_t pi)
{
	struct bnxt_softc *softc = (struct bnxt_softc *)sc;
	struct bnxt_ring *txr = &softc->tx_rings[pi->ipi_qsidx];
	struct tx_bd_long *tbd;
	struct tx_bd_long_hi *tbdh;
	bool need_hi = false;
	uint16_t flags_type;
	uint16_t lflags;
	uint32_t cfa_meta;
	int seg = 0;

	/* If we have offloads enabled, we need to use two BDs. */
	if ((pi->ipi_csum_flags & (CSUM_OFFLOAD | CSUM_TSO | CSUM_IP)) ||
	    pi->ipi_mflags & M_VLANTAG)
		need_hi = true;

	/* TODO: Devices before Cu+B1 need to not mix long and short BDs */
	need_hi = true;

	pi->ipi_new_pidx = pi->ipi_pidx;
	tbd = &((struct tx_bd_long *)txr->vaddr)[pi->ipi_new_pidx];
	pi->ipi_ndescs = 0;
	/* No need to byte-swap the opaque value */
	tbd->opaque = ((pi->ipi_nsegs + need_hi) << 24) | pi->ipi_new_pidx;
	tbd->len = htole16(pi->ipi_segs[seg].ds_len);
	tbd->addr = htole64(pi->ipi_segs[seg++].ds_addr);
	flags_type = ((pi->ipi_nsegs + need_hi) <<
	    TX_BD_SHORT_FLAGS_BD_CNT_SFT) & TX_BD_SHORT_FLAGS_BD_CNT_MASK;
	if (pi->ipi_len >= 2048)
		flags_type |= TX_BD_SHORT_FLAGS_LHINT_GTE2K;
	else
		flags_type |= bnxt_tx_lhint[pi->ipi_len >> 9];

	if (need_hi) {
		flags_type |= TX_BD_LONG_TYPE_TX_BD_LONG;

		pi->ipi_new_pidx = RING_NEXT(txr, pi->ipi_new_pidx);
		tbdh = &((struct tx_bd_long_hi *)txr->vaddr)[pi->ipi_new_pidx];
		tbdh->mss = htole16(pi->ipi_tso_segsz);
		tbdh->hdr_size = htole16((pi->ipi_ehdrlen + pi->ipi_ip_hlen +
		    pi->ipi_tcp_hlen) >> 1);
		tbdh->cfa_action = 0;
		lflags = 0;
		cfa_meta = 0;
		if (pi->ipi_mflags & M_VLANTAG) {
			/* TODO: Do we need to byte-swap the vtag here? */
			cfa_meta = TX_BD_LONG_CFA_META_KEY_VLAN_TAG |
			    pi->ipi_vtag;
			cfa_meta |= TX_BD_LONG_CFA_META_VLAN_TPID_TPID8100;
		}
		tbdh->cfa_meta = htole32(cfa_meta);
		if (pi->ipi_csum_flags & CSUM_TSO) {
			lflags |= TX_BD_LONG_LFLAGS_LSO |
			    TX_BD_LONG_LFLAGS_T_IPID;
		}
		else if(pi->ipi_csum_flags & CSUM_OFFLOAD) {
			lflags |= TX_BD_LONG_LFLAGS_TCP_UDP_CHKSUM |
			    TX_BD_LONG_LFLAGS_IP_CHKSUM;
		}
		else if(pi->ipi_csum_flags & CSUM_IP) {
			lflags |= TX_BD_LONG_LFLAGS_IP_CHKSUM;
		}
		tbdh->lflags = htole16(lflags);
	}
	else {
		flags_type |= TX_BD_SHORT_TYPE_TX_BD_SHORT;
	}

	for (; seg < pi->ipi_nsegs; seg++) {
		tbd->flags_type = htole16(flags_type);
		pi->ipi_new_pidx = RING_NEXT(txr, pi->ipi_new_pidx);
		tbd = &((struct tx_bd_long *)txr->vaddr)[pi->ipi_new_pidx];
		tbd->len = htole16(pi->ipi_segs[seg].ds_len);
		tbd->addr = htole64(pi->ipi_segs[seg].ds_addr);
		flags_type = TX_BD_SHORT_TYPE_TX_BD_SHORT;
	}
	flags_type |= TX_BD_SHORT_FLAGS_PACKET_END;
	tbd->flags_type = htole16(flags_type);
	pi->ipi_new_pidx = RING_NEXT(txr, pi->ipi_new_pidx);

	return 0;
}