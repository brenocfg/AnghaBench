#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int /*<<< orphan*/  truesize; scalar_t__ data; } ;
struct rx_inband_trailer {scalar_t__ stw_ovz; scalar_t__ stw_crc; } ;
struct rx_descriptor {int own; int id; unsigned int dataptr; unsigned int byteoff; unsigned int datalen; scalar_t__ c; scalar_t__ err; } ;
struct TYPE_8__ {scalar_t__ aal; } ;
struct atm_vcc {TYPE_3__* stats; TYPE_2__ qos; int /*<<< orphan*/  (* push ) (struct atm_vcc*,struct sk_buff*) ;} ;
struct TYPE_12__ {struct atm_vcc* vcc; } ;
struct TYPE_11__ {unsigned int vlddes; } ;
struct TYPE_10__ {size_t aal_desc_pos; struct rx_descriptor* aal_desc; int /*<<< orphan*/  wrx_drop_pdu; int /*<<< orphan*/  wrx_pdu; TYPE_1__* conn; } ;
struct TYPE_9__ {int /*<<< orphan*/  rx_drop; int /*<<< orphan*/  rx; int /*<<< orphan*/  rx_err; } ;
struct TYPE_7__ {int /*<<< orphan*/  aal5_vcc_oversize_sdu; int /*<<< orphan*/  aal5_vcc_crc_err; struct atm_vcc* vcc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int,char*,unsigned int,int,int,size_t) ; 
 scalar_t__ ATM_AAL5 ; 
 TYPE_6__* ATM_SKB (struct sk_buff*) ; 
 unsigned long LESS_CACHE_INV_LEN ; 
 unsigned int MAX_RX_PACKET_PADDING_BYTES ; 
 int /*<<< orphan*/  RX_DMA_CH_AAL ; 
 unsigned long RX_DMA_CH_AAL_BUF_SIZE ; 
 TYPE_5__* WRX_DMA_CHANNEL_CONFIG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adsl_led_flash () ; 
 struct sk_buff* alloc_skb_rx () ; 
 scalar_t__ atm_charge (struct atm_vcc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atm_return (struct atm_vcc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_cache_inv (unsigned long,unsigned long) ; 
 size_t dma_rx_descriptor_length ; 
 TYPE_4__ g_atm_priv_data ; 
 struct sk_buff* get_skb_rx_pointer (unsigned int) ; 
 int /*<<< orphan*/  mailbox_signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,unsigned long) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct atm_vcc*,struct sk_buff*) ; 

__attribute__((used)) static inline void mailbox_aal_rx_handler(void)
{
	unsigned int vlddes = WRX_DMA_CHANNEL_CONFIG(RX_DMA_CH_AAL)->vlddes;
	struct rx_descriptor reg_desc;
	int conn;
	struct atm_vcc *vcc;
	struct sk_buff *skb, *new_skb;
	struct rx_inband_trailer *trailer;
	unsigned int i;

	for ( i = 0; i < vlddes; i++ ) {
		unsigned int loop_count = 0;

		do {
			reg_desc = g_atm_priv_data.aal_desc[g_atm_priv_data.aal_desc_pos];
			if ( ++loop_count == 1000 )
				break;
		} while ( reg_desc.own || !reg_desc.c );    //  keep test OWN and C bit until data is ready
		ASSERT(loop_count == 1, "loop_count = %u, own = %d, c = %d, aal_desc_pos = %u", loop_count, (int)reg_desc.own, (int)reg_desc.c, g_atm_priv_data.aal_desc_pos);

		conn = reg_desc.id;

		if ( g_atm_priv_data.conn[conn].vcc != NULL ) {
			vcc = g_atm_priv_data.conn[conn].vcc;

			skb = get_skb_rx_pointer(reg_desc.dataptr);

			if ( reg_desc.err ) {
				if ( vcc->qos.aal == ATM_AAL5 ) {
					trailer = (struct rx_inband_trailer *)((unsigned int)skb->data + ((reg_desc.byteoff + reg_desc.datalen + MAX_RX_PACKET_PADDING_BYTES) & ~MAX_RX_PACKET_PADDING_BYTES));
					if ( trailer->stw_crc )
						g_atm_priv_data.conn[conn].aal5_vcc_crc_err++;
					if ( trailer->stw_ovz )
						g_atm_priv_data.conn[conn].aal5_vcc_oversize_sdu++;
					g_atm_priv_data.wrx_drop_pdu++;
				}
				if ( vcc->stats ) {
					atomic_inc(&vcc->stats->rx_drop);
					atomic_inc(&vcc->stats->rx_err);
				}
				reg_desc.err = 0;
			} else if ( atm_charge(vcc, skb->truesize) ) {
				new_skb = alloc_skb_rx();
				if ( new_skb != NULL ) {
#if defined(ENABLE_LESS_CACHE_INV) && ENABLE_LESS_CACHE_INV
					if ( reg_desc.byteoff + reg_desc.datalen > LESS_CACHE_INV_LEN )
						dma_cache_inv((unsigned long)skb->data + LESS_CACHE_INV_LEN, reg_desc.byteoff + reg_desc.datalen - LESS_CACHE_INV_LEN);
#endif

					skb_reserve(skb, reg_desc.byteoff);
					skb_put(skb, reg_desc.datalen);
					ATM_SKB(skb)->vcc = vcc;

					vcc->push(vcc, skb);

					if ( vcc->qos.aal == ATM_AAL5 )
						g_atm_priv_data.wrx_pdu++;
					if ( vcc->stats )
						atomic_inc(&vcc->stats->rx);
					adsl_led_flash();

					reg_desc.dataptr = (unsigned int)new_skb->data >> 2;
				} else {
					atm_return(vcc, skb->truesize);
					if ( vcc->qos.aal == ATM_AAL5 )
						g_atm_priv_data.wrx_drop_pdu++;
					if ( vcc->stats )
						atomic_inc(&vcc->stats->rx_drop);
				}
			} else {
				if ( vcc->qos.aal == ATM_AAL5 )
					g_atm_priv_data.wrx_drop_pdu++;
				if ( vcc->stats )
					atomic_inc(&vcc->stats->rx_drop);
			}
		} else {
			g_atm_priv_data.wrx_drop_pdu++;
		}

		reg_desc.byteoff = 0;
		reg_desc.datalen = RX_DMA_CH_AAL_BUF_SIZE;
		reg_desc.own = 1;
		reg_desc.c   = 0;

		g_atm_priv_data.aal_desc[g_atm_priv_data.aal_desc_pos] = reg_desc;
		if ( ++g_atm_priv_data.aal_desc_pos == dma_rx_descriptor_length )
			g_atm_priv_data.aal_desc_pos = 0;

		mailbox_signal(RX_DMA_CH_AAL, 0);
	}
}