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
struct wps_credential {int dummy; } ;
struct wpabuf {int dummy; } ;

/* Variables and functions */
 int ATTR_NETWORK_INDEX ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpabuf_put_be16 (struct wpabuf*,int) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,int) ; 

__attribute__((used)) static int wps_build_cred_network_idx(struct wpabuf *msg,
				      const struct wps_credential *cred)
{
	wpa_printf(MSG_DEBUG, "WPS:  * Network Index (1)");
	wpabuf_put_be16(msg, ATTR_NETWORK_INDEX);
	wpabuf_put_be16(msg, 1);
	wpabuf_put_u8(msg, 1);
	return 0;
}