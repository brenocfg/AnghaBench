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
struct eap_sm {int dummy; } ;
struct eap_pwd_data {int /*<<< orphan*/  session_id; int /*<<< orphan*/  emsk; int /*<<< orphan*/  msk; int /*<<< orphan*/  my_confirm; int /*<<< orphan*/  my_scalar; int /*<<< orphan*/  peer_scalar; int /*<<< orphan*/  k; TYPE_1__* grp; int /*<<< orphan*/  my_element; int /*<<< orphan*/  peer_element; int /*<<< orphan*/  group_num; } ;
struct crypto_hash {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  group; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_PWD_DEFAULT_PRF ; 
 int /*<<< orphan*/  EAP_PWD_DEFAULT_RAND_FUNC ; 
 int /*<<< orphan*/  FAILURE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int SHA256_MAC_LEN ; 
 int /*<<< orphan*/  SUCCESS ; 
 int /*<<< orphan*/  bin_clear_free (int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ compute_keys (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
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

__attribute__((used)) static void
eap_pwd_process_confirm_resp(struct eap_sm *sm, struct eap_pwd_data *data,
			     const u8 *payload, size_t payload_len)
{
	struct crypto_hash *hash = NULL;
	u32 cs;
	u16 grp;
	u8 conf[SHA256_MAC_LEN], *cruft = NULL, *ptr;
	size_t prime_len, order_len;

	prime_len = crypto_ec_prime_len(data->grp->group);
	order_len = crypto_ec_order_len(data->grp->group);

	if (payload_len != SHA256_MAC_LEN) {
		wpa_printf(MSG_INFO,
			   "EAP-pwd: Unexpected Confirm payload length %u (expected %u)",
			   (unsigned int) payload_len, SHA256_MAC_LEN);
		goto fin;
	}

	/* build up the ciphersuite: group | random_function | prf */
	grp = htons(data->group_num);
	ptr = (u8 *) &cs;
	os_memcpy(ptr, &grp, sizeof(u16));
	ptr += sizeof(u16);
	*ptr = EAP_PWD_DEFAULT_RAND_FUNC;
	ptr += sizeof(u8);
	*ptr = EAP_PWD_DEFAULT_PRF;

	/* each component of the cruft will be at most as big as the prime */
	cruft = os_malloc(prime_len * 2);
	if (!cruft) {
		wpa_printf(MSG_INFO, "EAP-PWD (peer): allocation fail");
		goto fin;
	}

	/*
	 * commit is H(k | peer_element | peer_scalar | server_element |
	 *	       server_scalar | ciphersuite)
	 */
	hash = eap_pwd_h_init();
	if (hash == NULL)
		goto fin;

	/* k */
	crypto_bignum_to_bin(data->k, cruft, prime_len, prime_len);
	eap_pwd_h_update(hash, cruft, prime_len);

	/* peer element: x, y */
	if (crypto_ec_point_to_bin(data->grp->group, data->peer_element, cruft,
				   cruft + prime_len) < 0) {
		wpa_printf(MSG_INFO, "EAP-PWD (server): confirm point "
			   "assignment fail");
		goto fin;
	}
	eap_pwd_h_update(hash, cruft, prime_len * 2);

	/* peer scalar */
	crypto_bignum_to_bin(data->peer_scalar, cruft, order_len, order_len);
	eap_pwd_h_update(hash, cruft, order_len);

	/* server element: x, y */
	if (crypto_ec_point_to_bin(data->grp->group, data->my_element, cruft,
				   cruft + prime_len) < 0) {
		wpa_printf(MSG_INFO, "EAP-PWD (server): confirm point "
			   "assignment fail");
		goto fin;
	}
	eap_pwd_h_update(hash, cruft, prime_len * 2);

	/* server scalar */
	crypto_bignum_to_bin(data->my_scalar, cruft, order_len, order_len);
	eap_pwd_h_update(hash, cruft, order_len);

	/* ciphersuite */
	eap_pwd_h_update(hash, (u8 *) &cs, sizeof(u32));

	/* all done */
	eap_pwd_h_final(hash, conf);
	hash = NULL;

	ptr = (u8 *) payload;
	if (os_memcmp_const(conf, ptr, SHA256_MAC_LEN)) {
		wpa_printf(MSG_INFO, "EAP-PWD (server): confirm did not "
			   "verify");
		goto fin;
	}

	wpa_printf(MSG_DEBUG, "EAP-pwd (server): confirm verified");
	if (compute_keys(data->grp, data->k,
			 data->peer_scalar, data->my_scalar, conf,
			 data->my_confirm, &cs, data->msk, data->emsk,
			 data->session_id) < 0)
		eap_pwd_state(data, FAILURE);
	else
		eap_pwd_state(data, SUCCESS);

fin:
	bin_clear_free(cruft, prime_len * 2);
	eap_pwd_h_final(hash, NULL);
}