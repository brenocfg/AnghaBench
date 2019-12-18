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
struct wps_data {int /*<<< orphan*/  keywrapkey; } ;
struct wpabuf {int dummy; } ;

/* Variables and functions */
 size_t const ATTR_ENCR_SETTINGS ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ aes_128_cbc_encrypt (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t const) ; 
 int /*<<< orphan*/  os_memset (int /*<<< orphan*/ *,size_t,size_t) ; 
 scalar_t__ random_get_bytes (int /*<<< orphan*/ *,size_t const) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 size_t const wpabuf_len (struct wpabuf*) ; 
 int /*<<< orphan*/ * wpabuf_put (struct wpabuf*,size_t const) ; 
 int /*<<< orphan*/  wpabuf_put_be16 (struct wpabuf*,size_t const) ; 
 int /*<<< orphan*/  wpabuf_put_buf (struct wpabuf*,struct wpabuf*) ; 

int wps_build_encr_settings(struct wps_data *wps, struct wpabuf *msg,
			    struct wpabuf *plain)
{
	size_t pad_len;
	const size_t block_size = 16;
	u8 *iv, *data;

	wpa_printf(MSG_DEBUG, "WPS:  * Encrypted Settings");

	/* PKCS#5 v2.0 pad */
	pad_len = block_size - wpabuf_len(plain) % block_size;
	os_memset(wpabuf_put(plain, pad_len), pad_len, pad_len);

	wpabuf_put_be16(msg, ATTR_ENCR_SETTINGS);
	wpabuf_put_be16(msg, block_size + wpabuf_len(plain));

	iv = wpabuf_put(msg, block_size);
	if (random_get_bytes(iv, block_size) < 0)
		return -1;

	data = wpabuf_put(msg, 0);
	wpabuf_put_buf(msg, plain);
	if (aes_128_cbc_encrypt(wps->keywrapkey, iv, data, wpabuf_len(plain)))
		return -1;

	return 0;
}