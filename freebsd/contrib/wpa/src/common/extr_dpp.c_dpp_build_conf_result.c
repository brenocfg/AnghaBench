#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct wpabuf {int dummy; } ;
struct dpp_authentication {TYPE_1__* curve; int /*<<< orphan*/  ke; int /*<<< orphan*/  e_nonce; } ;
typedef  enum dpp_status_error { ____Placeholder_dpp_status_error } dpp_status_error ;
struct TYPE_2__ {size_t nonce_len; int /*<<< orphan*/  hash_len; } ;

/* Variables and functions */
 int AES_BLOCK_SIZE ; 
 int DPP_ATTR_ENROLLEE_NONCE ; 
 int DPP_ATTR_WRAPPED_DATA ; 
 int /*<<< orphan*/  DPP_PA_CONFIGURATION_RESULT ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ aes_siv_encrypt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/  const**,size_t*,int /*<<< orphan*/ *) ; 
 struct wpabuf* dpp_alloc_msg (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  dpp_build_attr_status (struct wpabuf*,int) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpa_hexdump_buf (int /*<<< orphan*/ ,char*,struct wpabuf*) ; 
 struct wpabuf* wpabuf_alloc (size_t) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_head (struct wpabuf*) ; 
 int /*<<< orphan*/ * wpabuf_head_u8 (struct wpabuf*) ; 
 int wpabuf_len (struct wpabuf*) ; 
 void* wpabuf_put (struct wpabuf*,int) ; 
 int /*<<< orphan*/  wpabuf_put_data (struct wpabuf*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  wpabuf_put_le16 (struct wpabuf*,int) ; 

struct wpabuf * dpp_build_conf_result(struct dpp_authentication *auth,
				      enum dpp_status_error status)
{
	struct wpabuf *msg, *clear;
	size_t nonce_len, clear_len, attr_len;
	const u8 *addr[2];
	size_t len[2];
	u8 *wrapped;

	nonce_len = auth->curve->nonce_len;
	clear_len = 5 + 4 + nonce_len;
	attr_len = 4 + clear_len + AES_BLOCK_SIZE;
	clear = wpabuf_alloc(clear_len);
	msg = dpp_alloc_msg(DPP_PA_CONFIGURATION_RESULT, attr_len);
	if (!clear || !msg)
		return NULL;

	/* DPP Status */
	dpp_build_attr_status(clear, status);

	/* E-nonce */
	wpabuf_put_le16(clear, DPP_ATTR_ENROLLEE_NONCE);
	wpabuf_put_le16(clear, nonce_len);
	wpabuf_put_data(clear, auth->e_nonce, nonce_len);

	/* OUI, OUI type, Crypto Suite, DPP frame type */
	addr[0] = wpabuf_head_u8(msg) + 2;
	len[0] = 3 + 1 + 1 + 1;
	wpa_hexdump(MSG_DEBUG, "DDP: AES-SIV AD[0]", addr[0], len[0]);

	/* Attributes before Wrapped Data (none) */
	addr[1] = wpabuf_put(msg, 0);
	len[1] = 0;
	wpa_hexdump(MSG_DEBUG, "DDP: AES-SIV AD[1]", addr[1], len[1]);

	/* Wrapped Data */
	wpabuf_put_le16(msg, DPP_ATTR_WRAPPED_DATA);
	wpabuf_put_le16(msg, wpabuf_len(clear) + AES_BLOCK_SIZE);
	wrapped = wpabuf_put(msg, wpabuf_len(clear) + AES_BLOCK_SIZE);

	wpa_hexdump_buf(MSG_DEBUG, "DPP: AES-SIV cleartext", clear);
	if (aes_siv_encrypt(auth->ke, auth->curve->hash_len,
			    wpabuf_head(clear), wpabuf_len(clear),
			    2, addr, len, wrapped) < 0)
		goto fail;

	wpa_hexdump_buf(MSG_DEBUG, "DPP: Configuration Result attributes", msg);
	wpabuf_free(clear);
	return msg;
fail:
	wpabuf_free(clear);
	wpabuf_free(msg);
	return NULL;
}