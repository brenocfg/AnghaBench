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
struct ptm_itf {size_t tx_desc_pos; } ;
struct TYPE_4__ {scalar_t__ own; } ;
struct TYPE_3__ {struct ptm_itf* itf; } ;

/* Variables and functions */
 TYPE_2__* CPU_TO_WAN_TX_DESC_BASE ; 
 int CPU_TO_WAN_TX_DESC_NUM ; 
 TYPE_1__ g_ptm_priv_data ; 

__attribute__((used)) static inline int get_tx_desc(unsigned int itf, unsigned int *f_full)
{
    int desc_base = -1;
    struct ptm_itf *p_itf = &g_ptm_priv_data.itf[0];

    //  assume TX is serial operation
    //  no protection provided

    *f_full = 1;

    if ( CPU_TO_WAN_TX_DESC_BASE[p_itf->tx_desc_pos].own == 0 ) {
        desc_base = p_itf->tx_desc_pos;
        if ( ++(p_itf->tx_desc_pos) == CPU_TO_WAN_TX_DESC_NUM )
            p_itf->tx_desc_pos = 0;
        if ( CPU_TO_WAN_TX_DESC_BASE[p_itf->tx_desc_pos].own == 0 )
            *f_full = 0;
    }

    return desc_base;
}