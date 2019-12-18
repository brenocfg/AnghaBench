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
struct e1000_hw {int dummy; } ;

/* Variables and functions */
 int e1000_enable_tx_pkt_filtering_generic (struct e1000_hw*) ; 

bool e1000_enable_tx_pkt_filtering(struct e1000_hw *hw)
{
	return e1000_enable_tx_pkt_filtering_generic(hw);
}