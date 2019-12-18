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
typedef  int /*<<< orphan*/  u16 ;
struct eap_sm {int dummy; } ;
struct eap_pwd_data {int /*<<< orphan*/ * outbuf; int /*<<< orphan*/ * my_confirm; int /*<<< orphan*/  group_num; int /*<<< orphan*/  peer_scalar; int /*<<< orphan*/  peer_element; TYPE_1__* grp; int /*<<< orphan*/  my_scalar; int /*<<< orphan*/  my_element; int /*<<< orphan*/  k; scalar_t__ out_frag_pos; } ;
struct crypto_hash {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  group; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_PWD_DEFAULT_PRF ; 
 int /*<<< orphan*/  EAP_PWD_DEFAULT_RAND_FUNC ; 
 int /*<<< orphan*/  FAILURE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int SHA256_MAC_LEN ; 
 int /*<<< orphan*/  bin_clear_free (int /*<<< orphan*/ *,size_t) ; 
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
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  os_memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * wpabuf_alloc (int) ; 
 int /*<<< orphan*/  wpabuf_put_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void eap_pwd_build_confirm_req(struct eap_sm *sm,
				      struct eap_pwd_data *data, u8 id)
{
	struct crypto_hash *hash = NULL;
	u8 conf[SHA256_MAC_LEN], *cruft = NULL, *ptr;
	u16 grp;
	size_t prime_len, order_len;

	wpa_printf(MSG_DEBUG, "EAP-pwd: Confirm/Request");
	/*
	 * if we're fragmenting then we already have an confirm request, just
	 * return
	 */
	if (data->out_frag_pos)
		return;

	prime_len = crypto_ec_prime_len(data->grp->group);
	order_len = crypto_ec_order_len(data->grp->group);

	/* Each component of the cruft will be at most as big as the prime */
	cruft = os_malloc(prime_len * 2);
	if (!cruft) {
		wpa_printf(MSG_INFO, "EAP-PWD (server): debug allocation "
			   "fail");
		goto fin;
	}

	/*
	 * commit is H(k | server_element | server_scalar | peer_element |
	 *	       peer_scalar | ciphersuite)
	 */
	hash = eap_pwd_h_init();
	if (hash == NULL)
		goto fin;

	/*
	 * Zero the memory each time because this is mod prime math and some
	 * value may start with a few zeros and the previous one did not.
	 *
	 * First is k
	 */
	crypto_bignum_to_bin(data->k, cruft, prime_len, prime_len);
	eap_pwd_h_update(hash, cruft, prime_len);

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

	/* ciphersuite */
	grp = htons(data->group_num);
	os_memset(cruft, 0, prime_len);
	ptr = cruft;
	os_memcpy(ptr, &grp, sizeof(u16));
	ptr += sizeof(u16);
	*ptr = EAP_PWD_DEFAULT_RAND_FUNC;
	ptr += sizeof(u8);
	*ptr = EAP_PWD_DEFAULT_PRF;
	ptr += sizeof(u8);
	eap_pwd_h_update(hash, cruft, ptr - cruft);

	/* all done with the random function */
	eap_pwd_h_final(hash, conf);
	hash = NULL;
	os_memcpy(data->my_confirm, conf, SHA256_MAC_LEN);

	data->outbuf = wpabuf_alloc(SHA256_MAC_LEN);
	if (data->outbuf == NULL)
		goto fin;

	wpabuf_put_data(data->outbuf, conf, SHA256_MAC_LEN);

fin:
	bin_clear_free(cruft, prime_len * 2);
	if (data->outbuf == NULL)
		eap_pwd_state(data, FAILURE);
	eap_pwd_h_final(hash, NULL);
}