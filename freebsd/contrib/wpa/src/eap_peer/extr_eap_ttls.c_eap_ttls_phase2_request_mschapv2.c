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
typedef  int /*<<< orphan*/  const u8 ;
struct wpabuf {int dummy; } ;
struct eap_ttls_data {int auth_response_valid; int /*<<< orphan*/  master_key; int /*<<< orphan*/  auth_response; int /*<<< orphan*/  const ident; } ;
struct eap_sm {int dummy; } ;
struct eap_method_ret {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AVP_PAD (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int EAP_TTLS_MSCHAPV2_CHALLENGE_LEN ; 
 int /*<<< orphan*/  EAP_TTLS_MSCHAPV2_RESPONSE_LEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  RADIUS_ATTR_MS_CHAP2_RESPONSE ; 
 int /*<<< orphan*/  RADIUS_ATTR_MS_CHAP_CHALLENGE ; 
 int /*<<< orphan*/  RADIUS_ATTR_USER_NAME ; 
 int /*<<< orphan*/  RADIUS_VENDOR_ID_MICROSOFT ; 
 int /*<<< orphan*/  const* eap_get_config_identity (struct eap_sm*,size_t*) ; 
 int /*<<< orphan*/  const* eap_get_config_password2 (struct eap_sm*,size_t*,int*) ; 
 int /*<<< orphan*/  const* eap_ttls_avp_add (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  const* eap_ttls_avp_hdr (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const* eap_ttls_implicit_challenge (struct eap_sm*,struct eap_ttls_data*,int) ; 
 scalar_t__ mschapv2_derive_response (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*,size_t,int,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/  const*) ; 
 scalar_t__ os_get_random (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  os_memset (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 struct wpabuf* wpabuf_alloc (size_t) ; 
 int /*<<< orphan*/  wpabuf_clear_free (struct wpabuf*) ; 
 int /*<<< orphan*/  const* wpabuf_mhead (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_put (struct wpabuf*,int) ; 

__attribute__((used)) static int eap_ttls_phase2_request_mschapv2(struct eap_sm *sm,
					    struct eap_ttls_data *data,
					    struct eap_method_ret *ret,
					    struct wpabuf **resp)
{
#ifdef CONFIG_FIPS
	wpa_printf(MSG_ERROR, "EAP-TTLS: MSCHAPV2 not supported in FIPS build");
	return -1;
#else /* CONFIG_FIPS */
#ifdef EAP_MSCHAPv2
	struct wpabuf *msg;
	u8 *buf, *pos, *challenge, *peer_challenge;
	const u8 *identity, *password;
	size_t identity_len, password_len;
	int pwhash;

	wpa_printf(MSG_DEBUG, "EAP-TTLS: Phase 2 MSCHAPV2 Request");

	identity = eap_get_config_identity(sm, &identity_len);
	password = eap_get_config_password2(sm, &password_len, &pwhash);
	if (identity == NULL || password == NULL)
		return -1;

	msg = wpabuf_alloc(identity_len + 1000);
	if (msg == NULL) {
		wpa_printf(MSG_ERROR,
			   "EAP-TTLS/MSCHAPV2: Failed to allocate memory");
		return -1;
	}
	pos = buf = wpabuf_mhead(msg);

	/* User-Name */
	pos = eap_ttls_avp_add(buf, pos, RADIUS_ATTR_USER_NAME, 0, 1,
			       identity, identity_len);

	/* MS-CHAP-Challenge */
	challenge = eap_ttls_implicit_challenge(
		sm, data, EAP_TTLS_MSCHAPV2_CHALLENGE_LEN + 1);
	if (challenge == NULL) {
		wpabuf_clear_free(msg);
		wpa_printf(MSG_ERROR, "EAP-TTLS/MSCHAPV2: Failed to derive "
			   "implicit challenge");
		return -1;
	}

	pos = eap_ttls_avp_add(buf, pos, RADIUS_ATTR_MS_CHAP_CHALLENGE,
			       RADIUS_VENDOR_ID_MICROSOFT, 1,
			       challenge, EAP_TTLS_MSCHAPV2_CHALLENGE_LEN);

	/* MS-CHAP2-Response */
	pos = eap_ttls_avp_hdr(pos, RADIUS_ATTR_MS_CHAP2_RESPONSE,
			       RADIUS_VENDOR_ID_MICROSOFT, 1,
			       EAP_TTLS_MSCHAPV2_RESPONSE_LEN);
	data->ident = challenge[EAP_TTLS_MSCHAPV2_CHALLENGE_LEN];
	*pos++ = data->ident;
	*pos++ = 0; /* Flags */
	if (os_get_random(pos, EAP_TTLS_MSCHAPV2_CHALLENGE_LEN) < 0) {
		os_free(challenge);
		wpabuf_clear_free(msg);
		wpa_printf(MSG_ERROR, "EAP-TTLS/MSCHAPV2: Failed to get "
			   "random data for peer challenge");
		return -1;
	}
	peer_challenge = pos;
	pos += EAP_TTLS_MSCHAPV2_CHALLENGE_LEN;
	os_memset(pos, 0, 8); /* Reserved, must be zero */
	pos += 8;
	if (mschapv2_derive_response(identity, identity_len, password,
				     password_len, pwhash, challenge,
				     peer_challenge, pos, data->auth_response,
				     data->master_key)) {
		os_free(challenge);
		wpabuf_clear_free(msg);
		wpa_printf(MSG_ERROR, "EAP-TTLS/MSCHAPV2: Failed to derive "
			   "response");
		return -1;
	}
	data->auth_response_valid = 1;

	pos += 24;
	os_free(challenge);
	AVP_PAD(buf, pos);

	wpabuf_put(msg, pos - buf);
	*resp = msg;

	return 0;
#else /* EAP_MSCHAPv2 */
	wpa_printf(MSG_ERROR, "EAP-TTLS: MSCHAPv2 not included in the build");
	return -1;
#endif /* EAP_MSCHAPv2 */
#endif /* CONFIG_FIPS */
}