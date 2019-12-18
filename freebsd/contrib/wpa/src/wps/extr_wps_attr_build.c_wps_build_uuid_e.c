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
struct wpabuf {int dummy; } ;

/* Variables and functions */
 scalar_t__ ATTR_UUID_E ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ WPS_UUID_LEN ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpabuf_put_be16 (struct wpabuf*,scalar_t__) ; 
 int /*<<< orphan*/  wpabuf_put_data (struct wpabuf*,int /*<<< orphan*/  const*,scalar_t__) ; 
 scalar_t__ wpabuf_tailroom (struct wpabuf*) ; 

int wps_build_uuid_e(struct wpabuf *msg, const u8 *uuid)
{
	if (wpabuf_tailroom(msg) < 4 + WPS_UUID_LEN)
		return -1;
	wpa_printf(MSG_DEBUG, "WPS:  * UUID-E");
	wpabuf_put_be16(msg, ATTR_UUID_E);
	wpabuf_put_be16(msg, WPS_UUID_LEN);
	wpabuf_put_data(msg, uuid, WPS_UUID_LEN);
	return 0;
}