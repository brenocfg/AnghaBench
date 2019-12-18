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
struct sta_info {scalar_t__ last_rx_bytes_lo; scalar_t__ last_tx_bytes_lo; int /*<<< orphan*/  last_tx_bytes_hi; int /*<<< orphan*/  last_rx_bytes_hi; int /*<<< orphan*/  addr; } ;
struct hostapd_data {int dummy; } ;
struct hostap_sta_driver_data {scalar_t__ rx_bytes; scalar_t__ tx_bytes; int /*<<< orphan*/  bytes_64bit; } ;

/* Variables and functions */
 int /*<<< orphan*/  HOSTAPD_LEVEL_DEBUG ; 
 int /*<<< orphan*/  HOSTAPD_MODULE_RADIUS ; 
 scalar_t__ hostapd_drv_read_sta_data (struct hostapd_data*,struct hostap_sta_driver_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hostapd_logger (struct hostapd_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int accounting_sta_update_stats(struct hostapd_data *hapd,
				       struct sta_info *sta,
				       struct hostap_sta_driver_data *data)
{
	if (hostapd_drv_read_sta_data(hapd, data, sta->addr))
		return -1;

	if (!data->bytes_64bit) {
		/* Extend 32-bit counters from the driver to 64-bit counters */
		if (sta->last_rx_bytes_lo > data->rx_bytes)
			sta->last_rx_bytes_hi++;
		sta->last_rx_bytes_lo = data->rx_bytes;

		if (sta->last_tx_bytes_lo > data->tx_bytes)
			sta->last_tx_bytes_hi++;
		sta->last_tx_bytes_lo = data->tx_bytes;
	}

	hostapd_logger(hapd, sta->addr, HOSTAPD_MODULE_RADIUS,
		       HOSTAPD_LEVEL_DEBUG,
		       "updated TX/RX stats: rx_bytes=%llu [%u:%u] tx_bytes=%llu [%u:%u] bytes_64bit=%d",
		       data->rx_bytes, sta->last_rx_bytes_hi,
		       sta->last_rx_bytes_lo,
		       data->tx_bytes, sta->last_tx_bytes_hi,
		       sta->last_tx_bytes_lo,
		       data->bytes_64bit);

	return 0;
}