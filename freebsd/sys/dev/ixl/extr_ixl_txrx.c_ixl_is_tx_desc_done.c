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
struct tx_ring {TYPE_1__* tx_base; } ;
struct TYPE_2__ {int cmd_type_offset_bsz; } ;

/* Variables and functions */
 int I40E_TXD_QW1_DTYPE_MASK ; 
 int I40E_TXD_QW1_DTYPE_SHIFT ; 
 int I40E_TX_DESC_DTYPE_DESC_DONE ; 

__attribute__((used)) static bool
ixl_is_tx_desc_done(struct tx_ring *txr, int idx)
{
	return (((txr->tx_base[idx].cmd_type_offset_bsz >> I40E_TXD_QW1_DTYPE_SHIFT)
	    & I40E_TXD_QW1_DTYPE_MASK) == I40E_TX_DESC_DTYPE_DESC_DONE);
}