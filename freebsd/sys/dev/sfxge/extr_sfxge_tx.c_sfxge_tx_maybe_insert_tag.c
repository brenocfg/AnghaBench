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
typedef  scalar_t__ uint16_t ;
struct sfxge_txq {scalar_t__ hw_vlan_tci; size_t n_pend_desc; int /*<<< orphan*/  common; int /*<<< orphan*/ * pend_desc; } ;
struct sfxge_tx_mapping {int dummy; } ;
struct TYPE_2__ {scalar_t__ ether_vtag; } ;
struct mbuf {int m_flags; TYPE_1__ m_pkthdr; } ;
typedef  int /*<<< orphan*/  efx_desc_t ;

/* Variables and functions */
 int M_VLANTAG ; 
 int /*<<< orphan*/  bswap16 (scalar_t__) ; 
 int /*<<< orphan*/  efx_tx_qdesc_vlantci_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sfxge_next_stmp (struct sfxge_txq*,struct sfxge_tx_mapping**) ; 

__attribute__((used)) static int
sfxge_tx_maybe_insert_tag(struct sfxge_txq *txq, struct mbuf *mbuf,
			  struct sfxge_tx_mapping **pstmp)
{
	uint16_t this_tag = ((mbuf->m_flags & M_VLANTAG) ?
			     mbuf->m_pkthdr.ether_vtag :
			     0);
	efx_desc_t *desc;

	if (this_tag == txq->hw_vlan_tci)
		return (0);

	desc = &txq->pend_desc[txq->n_pend_desc];
	efx_tx_qdesc_vlantci_create(txq->common, bswap16(this_tag), desc);
	txq->hw_vlan_tci = this_tag;
	txq->n_pend_desc++;

	sfxge_next_stmp(txq, pstmp);

	return (1);
}