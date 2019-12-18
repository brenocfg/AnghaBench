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
typedef  enum wps_response_type { ____Placeholder_wps_response_type } wps_response_type ;

/* Variables and functions */
 int ATTR_RESPONSE_TYPE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  wpabuf_put_be16 (struct wpabuf*,int) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,int) ; 

int wps_build_resp_type(struct wpabuf *msg, enum wps_response_type type)
{
	wpa_printf(MSG_DEBUG, "WPS:  * Response Type (%d)", type);
	wpabuf_put_be16(msg, ATTR_RESPONSE_TYPE);
	wpabuf_put_be16(msg, 1);
	wpabuf_put_u8(msg, type);
	return 0;
}