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
struct mtk_ref2usb_tx {int /*<<< orphan*/  base_addr; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int REF2USB_EN_MASK ; 
 int readl (int /*<<< orphan*/ ) ; 
 struct mtk_ref2usb_tx* to_mtk_ref2usb_tx (struct clk_hw*) ; 

__attribute__((used)) static int mtk_ref2usb_tx_is_prepared(struct clk_hw *hw)
{
	struct mtk_ref2usb_tx *tx = to_mtk_ref2usb_tx(hw);

	return (readl(tx->base_addr) & REF2USB_EN_MASK) == REF2USB_EN_MASK;
}