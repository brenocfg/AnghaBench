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
struct TYPE_2__ {scalar_t__ usb_checksum; } ;
struct rtwn_tx_desc_common {TYPE_1__ txdw7; } ;

/* Variables and functions */
 scalar_t__ rtwn_usb_calc_tx_checksum (struct rtwn_tx_desc_common*) ; 

__attribute__((used)) static void
rtwn_usb_tx_checksum(struct rtwn_tx_desc_common *txd)
{
	txd->txdw7.usb_checksum = 0;
	txd->txdw7.usb_checksum = rtwn_usb_calc_tx_checksum(txd);
}