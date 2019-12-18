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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_PKEY ;

/* Variables and functions */
 size_t DPP_MAX_SHARED_SECRET_LEN ; 
 int /*<<< orphan*/  ERR_clear_error () ; 
 int ERR_error_string (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_get_error () ; 
 int /*<<< orphan*/  EVP_PKEY_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_CTX_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int EVP_PKEY_derive (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t*) ; 
 int EVP_PKEY_derive_init (int /*<<< orphan*/ *) ; 
 int EVP_PKEY_derive_set_peer (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int MSG_DEBUG ; 
 int MSG_ERROR ; 
 int /*<<< orphan*/  forced_memzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int,char*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int,char*,int) ; 

__attribute__((used)) static int dpp_ecdh(EVP_PKEY *own, EVP_PKEY *peer,
		    u8 *secret, size_t *secret_len)
{
	EVP_PKEY_CTX *ctx;
	int ret = -1;

	ERR_clear_error();
	*secret_len = 0;

	ctx = EVP_PKEY_CTX_new(own, NULL);
	if (!ctx) {
		wpa_printf(MSG_ERROR, "DPP: EVP_PKEY_CTX_new failed: %s",
			   ERR_error_string(ERR_get_error(), NULL));
		return -1;
	}

	if (EVP_PKEY_derive_init(ctx) != 1) {
		wpa_printf(MSG_ERROR, "DPP: EVP_PKEY_derive_init failed: %s",
			   ERR_error_string(ERR_get_error(), NULL));
		goto fail;
	}

	if (EVP_PKEY_derive_set_peer(ctx, peer) != 1) {
		wpa_printf(MSG_ERROR,
			   "DPP: EVP_PKEY_derive_set_peet failed: %s",
			   ERR_error_string(ERR_get_error(), NULL));
		goto fail;
	}

	if (EVP_PKEY_derive(ctx, NULL, secret_len) != 1) {
		wpa_printf(MSG_ERROR, "DPP: EVP_PKEY_derive(NULL) failed: %s",
			   ERR_error_string(ERR_get_error(), NULL));
		goto fail;
	}

	if (*secret_len > DPP_MAX_SHARED_SECRET_LEN) {
		u8 buf[200];
		int level = *secret_len > 200 ? MSG_ERROR : MSG_DEBUG;

		/* It looks like OpenSSL can return unexpectedly large buffer
		 * need for shared secret from EVP_PKEY_derive(NULL) in some
		 * cases. For example, group 19 has shown cases where secret_len
		 * is set to 72 even though the actual length ends up being
		 * updated to 32 when EVP_PKEY_derive() is called with a buffer
		 * for the value. Work around this by trying to fetch the value
		 * and continue if it is within supported range even when the
		 * initial buffer need is claimed to be larger. */
		wpa_printf(level,
			   "DPP: Unexpected secret_len=%d from EVP_PKEY_derive()",
			   (int) *secret_len);
		if (*secret_len > 200)
			goto fail;
		if (EVP_PKEY_derive(ctx, buf, secret_len) != 1) {
			wpa_printf(MSG_ERROR, "DPP: EVP_PKEY_derive failed: %s",
				   ERR_error_string(ERR_get_error(), NULL));
			goto fail;
		}
		if (*secret_len > DPP_MAX_SHARED_SECRET_LEN) {
			wpa_printf(MSG_ERROR,
				   "DPP: Unexpected secret_len=%d from EVP_PKEY_derive()",
				   (int) *secret_len);
			goto fail;
		}
		wpa_hexdump_key(MSG_DEBUG, "DPP: Unexpected secret_len change",
				buf, *secret_len);
		os_memcpy(secret, buf, *secret_len);
		forced_memzero(buf, sizeof(buf));
		goto done;
	}

	if (EVP_PKEY_derive(ctx, secret, secret_len) != 1) {
		wpa_printf(MSG_ERROR, "DPP: EVP_PKEY_derive failed: %s",
			   ERR_error_string(ERR_get_error(), NULL));
		goto fail;
	}

done:
	ret = 0;

fail:
	EVP_PKEY_CTX_free(ctx);
	return ret;
}