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
struct hci_uart {struct h5* priv; } ;
struct h5 {int /*<<< orphan*/  rx_func; } ;

/* Variables and functions */
 unsigned char SLIP_DELIMITER ; 
 int /*<<< orphan*/  h5_rx_pkt_start ; 

__attribute__((used)) static int h5_rx_delimiter(struct hci_uart *hu, unsigned char c)
{
	struct h5 *h5 = hu->priv;

	if (c == SLIP_DELIMITER)
		h5->rx_func = h5_rx_pkt_start;

	return 1;
}