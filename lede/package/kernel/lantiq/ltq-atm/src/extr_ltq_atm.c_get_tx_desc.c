#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct connection {size_t tx_desc_pos; TYPE_1__* tx_desc; } ;
struct TYPE_4__ {struct connection* conn; } ;
struct TYPE_3__ {scalar_t__ own; } ;

/* Variables and functions */
 int dma_tx_descriptor_length ; 
 TYPE_2__ g_atm_priv_data ; 

__attribute__((used)) static inline int get_tx_desc(unsigned int conn)
{
	int desc_base = -1;
	struct connection *p_conn = &g_atm_priv_data.conn[conn];

	if ( p_conn->tx_desc[p_conn->tx_desc_pos].own == 0 ) {
		desc_base = p_conn->tx_desc_pos;
		if ( ++(p_conn->tx_desc_pos) == dma_tx_descriptor_length )
			p_conn->tx_desc_pos = 0;
	}

	return desc_base;
}