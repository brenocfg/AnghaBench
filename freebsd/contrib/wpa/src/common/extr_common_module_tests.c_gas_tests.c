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
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  WLAN_ACTION_PUBLIC ; 
 int /*<<< orphan*/  WLAN_PA_GAS_INITIAL_REQ ; 
 int /*<<< orphan*/  gas_anqp_set_len (struct wpabuf*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 struct wpabuf* wpabuf_alloc (int) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_put_be32 (struct wpabuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gas_tests(void)
{
	struct wpabuf *buf;

	wpa_printf(MSG_INFO, "gas tests");
	gas_anqp_set_len(NULL);

	buf = wpabuf_alloc(1);
	if (buf == NULL)
		return -1;
	gas_anqp_set_len(buf);
	wpabuf_free(buf);

	buf = wpabuf_alloc(20);
	if (buf == NULL)
		return -1;
	wpabuf_put_u8(buf, WLAN_ACTION_PUBLIC);
	wpabuf_put_u8(buf, WLAN_PA_GAS_INITIAL_REQ);
	wpabuf_put_u8(buf, 0);
	wpabuf_put_be32(buf, 0);
	wpabuf_put_u8(buf, 0);
	gas_anqp_set_len(buf);
	wpabuf_free(buf);

	return 0;
}