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
struct dpp_signed_connector_info {unsigned char* payload; size_t payload_len; } ;
struct dpp_curve_params {int /*<<< orphan*/  jwk_crv; } ;
typedef  enum dpp_status_error { ____Placeholder_dpp_status_error } dpp_status_error ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;
typedef  int /*<<< orphan*/  EVP_MD ;
typedef  int /*<<< orphan*/  EC_KEY ;
typedef  int /*<<< orphan*/  EC_GROUP ;
typedef  int /*<<< orphan*/  ECDSA_SIG ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/ * BN_bin2bn (unsigned char*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int DPP_STATUS_INVALID_CONNECTOR ; 
 int DPP_STATUS_NO_MATCH ; 
 int DPP_STATUS_OK ; 
 int /*<<< orphan*/  ECDSA_SIG_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ECDSA_SIG_new () ; 
 int ECDSA_SIG_set0 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int EC_GROUP_get_curve_name (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EC_KEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_KEY_get0_group (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_clear_error () ; 
 scalar_t__ ERR_error_string (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_get_error () ; 
 int EVP_DigestVerifyFinal (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int EVP_DigestVerifyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int EVP_DigestVerifyUpdate (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_create () ; 
 int /*<<< orphan*/  EVP_MD_CTX_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_get1_EC_KEY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 scalar_t__ SHA256_MAC_LEN ; 
 void* base64_url_decode (unsigned char const*,int,size_t*) ; 
 scalar_t__ dpp_check_pubkey_match (int /*<<< orphan*/ *,struct wpabuf*) ; 
 struct dpp_curve_params* dpp_get_curve_nid (int) ; 
 struct wpabuf* dpp_parse_jws_prot_hdr (struct dpp_curve_params const*,unsigned char*,size_t,int /*<<< orphan*/  const**) ; 
 int i2d_ECDSA_SIG (int /*<<< orphan*/ *,unsigned char**) ; 
 int /*<<< orphan*/  os_free (unsigned char*) ; 
 int /*<<< orphan*/  os_memset (struct dpp_signed_connector_info*,int /*<<< orphan*/ ,int) ; 
 char* os_strchr (char const*,char) ; 
 int os_strlen (char const*) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,unsigned char*,int) ; 
 int /*<<< orphan*/  wpa_hexdump_ascii (int /*<<< orphan*/ ,char*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 scalar_t__ wpabuf_len (struct wpabuf*) ; 

__attribute__((used)) static enum dpp_status_error
dpp_process_signed_connector(struct dpp_signed_connector_info *info,
			     EVP_PKEY *csign_pub, const char *connector)
{
	enum dpp_status_error ret = 255;
	const char *pos, *end, *signed_start, *signed_end;
	struct wpabuf *kid = NULL;
	unsigned char *prot_hdr = NULL, *signature = NULL;
	size_t prot_hdr_len = 0, signature_len = 0;
	const EVP_MD *sign_md = NULL;
	unsigned char *der = NULL;
	int der_len;
	int res;
	EVP_MD_CTX *md_ctx = NULL;
	ECDSA_SIG *sig = NULL;
	BIGNUM *r = NULL, *s = NULL;
	const struct dpp_curve_params *curve;
	EC_KEY *eckey;
	const EC_GROUP *group;
	int nid;

	eckey = EVP_PKEY_get1_EC_KEY(csign_pub);
	if (!eckey)
		goto fail;
	group = EC_KEY_get0_group(eckey);
	if (!group)
		goto fail;
	nid = EC_GROUP_get_curve_name(group);
	curve = dpp_get_curve_nid(nid);
	if (!curve)
		goto fail;
	wpa_printf(MSG_DEBUG, "DPP: C-sign-key group: %s", curve->jwk_crv);
	os_memset(info, 0, sizeof(*info));

	signed_start = pos = connector;
	end = os_strchr(pos, '.');
	if (!end) {
		wpa_printf(MSG_DEBUG, "DPP: Missing dot(1) in signedConnector");
		ret = DPP_STATUS_INVALID_CONNECTOR;
		goto fail;
	}
	prot_hdr = base64_url_decode((const unsigned char *) pos,
				     end - pos, &prot_hdr_len);
	if (!prot_hdr) {
		wpa_printf(MSG_DEBUG,
			   "DPP: Failed to base64url decode signedConnector JWS Protected Header");
		ret = DPP_STATUS_INVALID_CONNECTOR;
		goto fail;
	}
	wpa_hexdump_ascii(MSG_DEBUG,
			  "DPP: signedConnector - JWS Protected Header",
			  prot_hdr, prot_hdr_len);
	kid = dpp_parse_jws_prot_hdr(curve, prot_hdr, prot_hdr_len, &sign_md);
	if (!kid) {
		ret = DPP_STATUS_INVALID_CONNECTOR;
		goto fail;
	}
	if (wpabuf_len(kid) != SHA256_MAC_LEN) {
		wpa_printf(MSG_DEBUG,
			   "DPP: Unexpected signedConnector JWS Protected Header kid length: %u (expected %u)",
			   (unsigned int) wpabuf_len(kid), SHA256_MAC_LEN);
		ret = DPP_STATUS_INVALID_CONNECTOR;
		goto fail;
	}

	pos = end + 1;
	end = os_strchr(pos, '.');
	if (!end) {
		wpa_printf(MSG_DEBUG,
			   "DPP: Missing dot(2) in signedConnector");
		ret = DPP_STATUS_INVALID_CONNECTOR;
		goto fail;
	}
	signed_end = end - 1;
	info->payload = base64_url_decode((const unsigned char *) pos,
					  end - pos, &info->payload_len);
	if (!info->payload) {
		wpa_printf(MSG_DEBUG,
			   "DPP: Failed to base64url decode signedConnector JWS Payload");
		ret = DPP_STATUS_INVALID_CONNECTOR;
		goto fail;
	}
	wpa_hexdump_ascii(MSG_DEBUG,
			  "DPP: signedConnector - JWS Payload",
			  info->payload, info->payload_len);
	pos = end + 1;
	signature = base64_url_decode((const unsigned char *) pos,
				      os_strlen(pos), &signature_len);
	if (!signature) {
		wpa_printf(MSG_DEBUG,
			   "DPP: Failed to base64url decode signedConnector signature");
		ret = DPP_STATUS_INVALID_CONNECTOR;
		goto fail;
		}
	wpa_hexdump(MSG_DEBUG, "DPP: signedConnector - signature",
		    signature, signature_len);

	if (dpp_check_pubkey_match(csign_pub, kid) < 0) {
		ret = DPP_STATUS_NO_MATCH;
		goto fail;
	}

	if (signature_len & 0x01) {
		wpa_printf(MSG_DEBUG,
			   "DPP: Unexpected signedConnector signature length (%d)",
			   (int) signature_len);
		ret = DPP_STATUS_INVALID_CONNECTOR;
		goto fail;
	}

	/* JWS Signature encodes the signature (r,s) as two octet strings. Need
	 * to convert that to DER encoded ECDSA_SIG for OpenSSL EVP routines. */
	r = BN_bin2bn(signature, signature_len / 2, NULL);
	s = BN_bin2bn(signature + signature_len / 2, signature_len / 2, NULL);
	sig = ECDSA_SIG_new();
	if (!r || !s || !sig || ECDSA_SIG_set0(sig, r, s) != 1)
		goto fail;
	r = NULL;
	s = NULL;

	der_len = i2d_ECDSA_SIG(sig, &der);
	if (der_len <= 0) {
		wpa_printf(MSG_DEBUG, "DPP: Could not DER encode signature");
		goto fail;
	}
	wpa_hexdump(MSG_DEBUG, "DPP: DER encoded signature", der, der_len);
	md_ctx = EVP_MD_CTX_create();
	if (!md_ctx)
		goto fail;

	ERR_clear_error();
	if (EVP_DigestVerifyInit(md_ctx, NULL, sign_md, NULL, csign_pub) != 1) {
		wpa_printf(MSG_DEBUG, "DPP: EVP_DigestVerifyInit failed: %s",
			   ERR_error_string(ERR_get_error(), NULL));
		goto fail;
	}
	if (EVP_DigestVerifyUpdate(md_ctx, signed_start,
				   signed_end - signed_start + 1) != 1) {
		wpa_printf(MSG_DEBUG, "DPP: EVP_DigestVerifyUpdate failed: %s",
			   ERR_error_string(ERR_get_error(), NULL));
		goto fail;
	}
	res = EVP_DigestVerifyFinal(md_ctx, der, der_len);
	if (res != 1) {
		wpa_printf(MSG_DEBUG,
			   "DPP: EVP_DigestVerifyFinal failed (res=%d): %s",
			   res, ERR_error_string(ERR_get_error(), NULL));
		ret = DPP_STATUS_INVALID_CONNECTOR;
		goto fail;
	}

	ret = DPP_STATUS_OK;
fail:
	EC_KEY_free(eckey);
	EVP_MD_CTX_destroy(md_ctx);
	os_free(prot_hdr);
	wpabuf_free(kid);
	os_free(signature);
	ECDSA_SIG_free(sig);
	BN_free(r);
	BN_free(s);
	OPENSSL_free(der);
	return ret;
}