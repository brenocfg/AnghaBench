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
struct sk_buff {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/ * aal_desc_base; TYPE_2__* aal_desc; int /*<<< orphan*/ * oam_desc_base; int /*<<< orphan*/ * oam_buf_base; int /*<<< orphan*/ * tx_desc_base; int /*<<< orphan*/ * tx_skb_base; TYPE_1__* conn; } ;
struct TYPE_5__ {int /*<<< orphan*/  dataptr; scalar_t__ eop; scalar_t__ sop; } ;
struct TYPE_4__ {struct sk_buff** tx_skb; } ;

/* Variables and functions */
 int MAX_PVC_NUMBER ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int dma_rx_descriptor_length ; 
 int dma_tx_descriptor_length ; 
 TYPE_3__ g_atm_priv_data ; 
 struct sk_buff* get_skb_rx_pointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void clear_priv_data(void)
{
	int i, j;
	struct sk_buff *skb;

	for ( i = 0; i < MAX_PVC_NUMBER; i++ ) {
		if ( g_atm_priv_data.conn[i].tx_skb != NULL ) {
			for ( j = 0; j < dma_tx_descriptor_length; j++ )
				if ( g_atm_priv_data.conn[i].tx_skb[j] != NULL )
					dev_kfree_skb_any(g_atm_priv_data.conn[i].tx_skb[j]);
		}
	}

	if ( g_atm_priv_data.tx_skb_base != NULL )
		kfree(g_atm_priv_data.tx_skb_base);

	if ( g_atm_priv_data.tx_desc_base != NULL )
		kfree(g_atm_priv_data.tx_desc_base);

	if ( g_atm_priv_data.oam_buf_base != NULL )
		kfree(g_atm_priv_data.oam_buf_base);

	if ( g_atm_priv_data.oam_desc_base != NULL )
		kfree(g_atm_priv_data.oam_desc_base);

	if ( g_atm_priv_data.aal_desc_base != NULL ) {
		for ( i = 0; i < dma_rx_descriptor_length; i++ ) {
			if ( g_atm_priv_data.aal_desc[i].sop || g_atm_priv_data.aal_desc[i].eop ) { //  descriptor initialized
				skb = get_skb_rx_pointer(g_atm_priv_data.aal_desc[i].dataptr);
				dev_kfree_skb_any(skb);
			}
		}
		kfree(g_atm_priv_data.aal_desc_base);
	}
}