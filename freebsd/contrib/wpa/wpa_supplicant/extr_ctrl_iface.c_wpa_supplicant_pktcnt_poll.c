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
struct wpa_supplicant {int dummy; } ;
struct hostap_sta_driver_data {int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  tx_retry_failed; int /*<<< orphan*/  tx_packets; } ;

/* Variables and functions */
 int os_snprintf (char*,size_t,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ os_snprintf_error (size_t,int) ; 
 int wpa_drv_pktcnt_poll (struct wpa_supplicant*,struct hostap_sta_driver_data*) ; 

__attribute__((used)) static int wpa_supplicant_pktcnt_poll(struct wpa_supplicant *wpa_s, char *buf,
				      size_t buflen)
{
	struct hostap_sta_driver_data sta;
	int ret;

	ret = wpa_drv_pktcnt_poll(wpa_s, &sta);
	if (ret)
		return -1;

	ret = os_snprintf(buf, buflen, "TXGOOD=%lu\nTXBAD=%lu\nRXGOOD=%lu\n",
			  sta.tx_packets, sta.tx_retry_failed, sta.rx_packets);
	if (os_snprintf_error(buflen, ret))
		return -1;
	return ret;
}