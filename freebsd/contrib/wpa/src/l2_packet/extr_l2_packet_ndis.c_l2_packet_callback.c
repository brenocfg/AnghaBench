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
typedef  int /*<<< orphan*/  u8 ;
struct l2_packet_data {int rx_written; int /*<<< orphan*/  rx_callback_ctx; int /*<<< orphan*/  (* rx_callback ) (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t) ;scalar_t__ l2_hdr; scalar_t__ rx_buf; } ;
struct l2_ethhdr {int /*<<< orphan*/ * h_source; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  l2_ndisuio_start_read (struct l2_packet_data*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void l2_packet_callback(struct l2_packet_data *l2)
{
	const u8 *rx_buf, *rx_src;
	size_t rx_len;
	struct l2_ethhdr *ethhdr = (struct l2_ethhdr *) l2->rx_buf;

	wpa_printf(MSG_DEBUG, "L2(NDISUIO): Read %d bytes",
		   (int) l2->rx_written);

	if (l2->l2_hdr || l2->rx_written < sizeof(*ethhdr)) {
		rx_buf = (u8 *) ethhdr;
		rx_len = l2->rx_written;
	} else {
		rx_buf = (u8 *) (ethhdr + 1);
		rx_len = l2->rx_written - sizeof(*ethhdr);
	}
	rx_src = ethhdr->h_source;

	l2->rx_callback(l2->rx_callback_ctx, rx_src, rx_buf, rx_len);
#ifndef _WIN32_WCE
	l2_ndisuio_start_read(l2, 1);
#endif /* _WIN32_WCE */
}