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
struct vas_rx_win_attr {int pin_win; int nx_win; int fault_win; int intr_disable; int rx_wcred_mode; int tx_wcred_mode; int rx_win_ord_mode; int tx_win_ord_mode; int notify_disable; int user_win; } ;
typedef  enum vas_cop_type { ____Placeholder_vas_cop_type } vas_cop_type ;

/* Variables and functions */
 int VAS_COP_TYPE_842 ; 
 int VAS_COP_TYPE_842_HIPRI ; 
 int VAS_COP_TYPE_FAULT ; 
 int VAS_COP_TYPE_FTW ; 
 int /*<<< orphan*/  memset (struct vas_rx_win_attr*,int /*<<< orphan*/ ,int) ; 

void vas_init_rx_win_attr(struct vas_rx_win_attr *rxattr, enum vas_cop_type cop)
{
	memset(rxattr, 0, sizeof(*rxattr));

	if (cop == VAS_COP_TYPE_842 || cop == VAS_COP_TYPE_842_HIPRI) {
		rxattr->pin_win = true;
		rxattr->nx_win = true;
		rxattr->fault_win = false;
		rxattr->intr_disable = true;
		rxattr->rx_wcred_mode = true;
		rxattr->tx_wcred_mode = true;
		rxattr->rx_win_ord_mode = true;
		rxattr->tx_win_ord_mode = true;
	} else if (cop == VAS_COP_TYPE_FAULT) {
		rxattr->pin_win = true;
		rxattr->fault_win = true;
		rxattr->notify_disable = true;
		rxattr->rx_wcred_mode = true;
		rxattr->tx_wcred_mode = true;
		rxattr->rx_win_ord_mode = true;
		rxattr->tx_win_ord_mode = true;
	} else if (cop == VAS_COP_TYPE_FTW) {
		rxattr->user_win = true;
		rxattr->intr_disable = true;

		/*
		 * As noted in the VAS Workbook we disable credit checks.
		 * If we enable credit checks in the future, we must also
		 * implement a mechanism to return the user credits or new
		 * paste operations will fail.
		 */
	}
}