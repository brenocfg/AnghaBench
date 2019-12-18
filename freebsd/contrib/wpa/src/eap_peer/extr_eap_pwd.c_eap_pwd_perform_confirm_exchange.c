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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct wpabuf {int dummy; } ;
struct eap_sm {int dummy; } ;
struct eap_pwd_data {scalar_t__ state; int /*<<< orphan*/ * outbuf; int /*<<< orphan*/  session_id; int /*<<< orphan*/  emsk; int /*<<< orphan*/  msk; int /*<<< orphan*/  server_scalar; int /*<<< orphan*/  my_scalar; int /*<<< orphan*/  k; TYPE_1__* grp; int /*<<< orphan*/  server_element; int /*<<< orphan*/  my_element; int /*<<< orphan*/  group_num; } ;
struct eap_method_ret {int /*<<< orphan*/  decision; int /*<<< orphan*/  methodState; int /*<<< orphan*/  ignore; } ;
struct crypto_hash {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  group; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECISION_FAIL ; 
 int /*<<< orphan*/  EAP_PWD_DEFAULT_PRF ; 
 int /*<<< orphan*/  EAP_PWD_DEFAULT_RAND_FUNC ; 
 int /*<<< orphan*/  FAILURE ; 
 int /*<<< orphan*/  METHOD_DONE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 scalar_t__ PWD_Confirm_Req ; 
 int SHA256_MAC_LEN ; 
 int /*<<< orphan*/  SUCCESS_ON_FRAG_COMPLETION ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bin_clear_free (int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ compute_keys (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_bignum_to_bin (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,size_t) ; 
 size_t crypto_ec_order_len (int /*<<< orphan*/ ) ; 
 scalar_t__ crypto_ec_point_to_bin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t crypto_ec_prime_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_pwd_h_final (struct crypto_hash*,int /*<<< orphan*/ *) ; 
 struct crypto_hash* eap_pwd_h_init () ; 
 int /*<<< orphan*/  eap_pwd_h_update (struct crypto_hash*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  eap_pwd_state (struct eap_pwd_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * os_malloc (size_t) ; 
 scalar_t__ os_memcmp_const (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * wpabuf_alloc (int) ; 
 int /*<<< orphan*/  wpabuf_put_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
eap_pwd_perform_confirm_exchange(struct eap_sm *sm, struct eap_pwd_data *data,
				 struct eap_method_ret *ret,
				 const struct wpabuf *reqData,
				 const u8 *payload, size_t payload_len)
{
	struct crypto_hash *hash = NULL;
	u32 cs;
	u16 grp;
	u8 conf[SHA256_MAC_LEN], *cruft = NULL, *ptr;
	size_t prime_len = 0, order_len = 0;

	if (data->state != PWD_Confirm_Req) {
		ret->ignore = TRUE;
		goto fin;
	}

	if (payload_len != SHA256_MAC_LEN) {
		wpa_printf(MSG_INFO,
			   "EAP-pwd: Unexpected Confirm payload length %u (expected %u)",
			   (unsigned int) payload_len, SHA256_MAC_LEN);
		goto fin;
	}

	prime_len = crypto_ec_prime_len(data->grp->group);
	order_len = crypto_ec_order_len(data->grp->group);

	/*
	 * first build up the ciphersuite which is group | random_function |
	 *	prf
	 */
	grp = htons(data->group_num);
	ptr = (u8 *) &cs;
	os_memcpy(ptr, &grp, sizeof(u16));
	ptr += sizeof(u16);
	*ptr = EAP_PWD_DEFAULT_RAND_FUNC;
	ptr += sizeof(u8);
	*ptr = EAP_PWD_DEFAULT_PRF;

	/* each component of the point will be at most as big as the prime */
	cruft = os_malloc(prime_len * 2);
	if (!cruft) {
		wpa_printf(MSG_INFO, "EAP-PWD (server): confirm allocation "
			   "fail");
		goto fin;
	}

	/*
	 * server's commit is H(k | server_element | server_scalar |
	 *			peer_element | peer_scalar | ciphersuite)
	 */
	hash = eap_pwd_h_init();
	if (hash == NULL)
		goto fin;

	/*
	 * zero the memory each time because this is mod prime math and some
	 * value may start with a few zeros and the previous one did not.
	 */
	crypto_bignum_to_bin(data->k, cruft, prime_len, prime_len);
	eap_pwd_h_update(hash, cruft, prime_len);

	/* server element: x, y */
	if (crypto_ec_point_to_bin(data->grp->group, data->server_element,
				   cruft, cruft + prime_len) != 0) {
		wpa_printf(MSG_INFO, "EAP-PWD (server): confirm point "
			   "assignment fail");
		goto fin;
	}
	eap_pwd_h_update(hash, cruft, prime_len * 2);

	/* server scalar */
	crypto_bignum_to_bin(data->server_scalar, cruft, order_len, order_len);
	eap_pwd_h_update(hash, cruft, order_len);

	/* my element: x, y */
	if (crypto_ec_point_to_bin(data->grp->group, data->my_element, cruft,
				   cruft + prime_len) != 0) {
		wpa_printf(MSG_INFO, "EAP-PWD (server): confirm point "
			   "assignment fail");
		goto fin;
	}
	eap_pwd_h_update(hash, cruft, prime_len * 2);

	/* my scalar */
	crypto_bignum_to_bin(data->my_scalar, cruft, order_len, order_len);
	eap_pwd_h_update(hash, cruft, order_len);

	/* the ciphersuite */
	eap_pwd_h_update(hash, (u8 *) &cs, sizeof(u32));

	/* random function fin */
	eap_pwd_h_final(hash, conf);
	hash = NULL;

	ptr = (u8 *) payload;
	if (os_memcmp_const(conf, ptr, SHA256_MAC_LEN)) {
		wpa_printf(MSG_INFO, "EAP-PWD (peer): confirm did not verify");
		goto fin;
	}

	wpa_printf(MSG_DEBUG, "EAP-pwd (peer): confirm verified");

	/*
	 * compute confirm:
	 *  H(k | peer_element | peer_scalar | server_element | server_scalar |
	 *    ciphersuite)
	 */
	hash = eap_pwd_h_init();
	if (hash == NULL)
		goto fin;

	/* k */
	crypto_bignum_to_bin(data->k, cruft, prime_len, prime_len);
	eap_pwd_h_update(hash, cruft, prime_len);

	/* my element */
	if (crypto_ec_point_to_bin(data->grp->group, data->my_element, cruft,
				   cruft + prime_len) != 0) {
		wpa_printf(MSG_INFO, "EAP-PWD (peer): confirm point "
			   "assignment fail");
		goto fin;
	}
	eap_pwd_h_update(hash, cruft, prime_len * 2);

	/* my scalar */
	crypto_bignum_to_bin(data->my_scalar, cruft, order_len, order_len);
	eap_pwd_h_update(hash, cruft, order_len);

	/* server element: x, y */
	if (crypto_ec_point_to_bin(data->grp->group, data->server_element,
				   cruft, cruft + prime_len) != 0) {
		wpa_printf(MSG_INFO, "EAP-PWD (peer): confirm point "
			   "assignment fail");
		goto fin;
	}
	eap_pwd_h_update(hash, cruft, prime_len * 2);

	/* server scalar */
	crypto_bignum_to_bin(data->server_scalar, cruft, order_len, order_len);
	eap_pwd_h_update(hash, cruft, order_len);

	/* the ciphersuite */
	eap_pwd_h_update(hash, (u8 *) &cs, sizeof(u32));

	/* all done */
	eap_pwd_h_final(hash, conf);
	hash = NULL;

	if (compute_keys(data->grp, data->k,
			 data->my_scalar, data->server_scalar, conf, ptr,
			 &cs, data->msk, data->emsk, data->session_id) < 0) {
		wpa_printf(MSG_INFO, "EAP-PWD (peer): unable to compute MSK | "
			   "EMSK");
		goto fin;
	}

	data->outbuf = wpabuf_alloc(SHA256_MAC_LEN);
	if (data->outbuf == NULL)
		goto fin;

	wpabuf_put_data(data->outbuf, conf, SHA256_MAC_LEN);

fin:
	bin_clear_free(cruft, prime_len * 2);
	if (data->outbuf == NULL) {
		ret->methodState = METHOD_DONE;
		ret->decision = DECISION_FAIL;
		eap_pwd_state(data, FAILURE);
	} else {
		eap_pwd_state(data, SUCCESS_ON_FRAG_COMPLETION);
	}

	/* clean allocated memory */
	if (hash)
		eap_pwd_h_final(hash, conf);
}