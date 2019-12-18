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
typedef  unsigned char u8 ;
struct h5 {int /*<<< orphan*/  rx_pending; int /*<<< orphan*/  rx_skb; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,unsigned char const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BT_ERR (char*,unsigned char) ; 
 int /*<<< orphan*/  H5_RX_ESC ; 
 unsigned char SLIP_DELIMITER ; 
 unsigned char SLIP_ESC ; 
#define  SLIP_ESC_DELIM 129 
#define  SLIP_ESC_ESC 128 
 int /*<<< orphan*/  h5_reset_rx (struct h5*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_put_data (int /*<<< orphan*/ ,unsigned char const*,int) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void h5_unslip_one_byte(struct h5 *h5, unsigned char c)
{
	const u8 delim = SLIP_DELIMITER, esc = SLIP_ESC;
	const u8 *byte = &c;

	if (!test_bit(H5_RX_ESC, &h5->flags) && c == SLIP_ESC) {
		set_bit(H5_RX_ESC, &h5->flags);
		return;
	}

	if (test_and_clear_bit(H5_RX_ESC, &h5->flags)) {
		switch (c) {
		case SLIP_ESC_DELIM:
			byte = &delim;
			break;
		case SLIP_ESC_ESC:
			byte = &esc;
			break;
		default:
			BT_ERR("Invalid esc byte 0x%02hhx", c);
			h5_reset_rx(h5);
			return;
		}
	}

	skb_put_data(h5->rx_skb, byte, 1);
	h5->rx_pending--;

	BT_DBG("unslipped 0x%02hhx, rx_pending %zu", *byte, h5->rx_pending);
}