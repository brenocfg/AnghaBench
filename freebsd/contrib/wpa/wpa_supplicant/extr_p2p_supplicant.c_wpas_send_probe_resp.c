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
struct wpabuf {int dummy; } ;
struct wpa_supplicant {int dummy; } ;

/* Variables and functions */
 int wpa_drv_send_mlme (struct wpa_supplicant*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int) ; 
 int /*<<< orphan*/  wpabuf_head (struct wpabuf const*) ; 
 int /*<<< orphan*/  wpabuf_len (struct wpabuf const*) ; 

__attribute__((used)) static int wpas_send_probe_resp(void *ctx, const struct wpabuf *buf,
				unsigned int freq)
{
	struct wpa_supplicant *wpa_s = ctx;
	return wpa_drv_send_mlme(wpa_s, wpabuf_head(buf), wpabuf_len(buf), 1,
				 freq);
}