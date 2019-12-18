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
typedef  int u16 ;
struct wpabuf {int dummy; } ;

/* Variables and functions */
 int ATTR_AP_CHANNEL ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  wpabuf_put_be16 (struct wpabuf*,int) ; 

int wps_build_ap_channel(struct wpabuf *msg, u16 ap_channel)
{
	wpa_printf(MSG_DEBUG, "WPS:  * AP Channel (%u)", ap_channel);
	wpabuf_put_be16(msg, ATTR_AP_CHANNEL);
	wpabuf_put_be16(msg, 2);
	wpabuf_put_be16(msg, ap_channel);
	return 0;
}