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

/* Variables and functions */
 int ATTR_VERSION ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpabuf_put_be16 (struct wpabuf*,int) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,int) ; 
 int wpabuf_tailroom (struct wpabuf*) ; 

int wps_build_version(struct wpabuf *msg)
{
	/*
	 * Note: This attribute is deprecated and set to hardcoded 0x10 for
	 * backwards compatibility reasons. The real version negotiation is
	 * done with Version2.
	 */
	if (wpabuf_tailroom(msg) < 5)
		return -1;
	wpa_printf(MSG_DEBUG, "WPS:  * Version (hardcoded 0x10)");
	wpabuf_put_be16(msg, ATTR_VERSION);
	wpabuf_put_be16(msg, 1);
	wpabuf_put_u8(msg, 0x10);
	return 0;
}