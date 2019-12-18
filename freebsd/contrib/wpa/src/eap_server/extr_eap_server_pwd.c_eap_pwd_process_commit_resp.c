#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct eap_sm {int dummy; } ;
struct eap_pwd_data {int /*<<< orphan*/  k; TYPE_1__* grp; int /*<<< orphan*/  private_value; int /*<<< orphan*/  peer_element; int /*<<< orphan*/  peer_scalar; int /*<<< orphan*/  my_element; int /*<<< orphan*/  my_scalar; } ;
struct crypto_ec_point {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  group; struct crypto_ec_point* pwe; } ;

/* Variables and functions */
 int /*<<< orphan*/  FAILURE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  PWD_Confirm_Req ; 
 scalar_t__ crypto_bignum_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_bignum_init () ; 
 size_t crypto_ec_order_len (int /*<<< orphan*/ ) ; 
 scalar_t__ crypto_ec_point_add (int /*<<< orphan*/ ,struct crypto_ec_point*,int /*<<< orphan*/ ,struct crypto_ec_point*) ; 
 scalar_t__ crypto_ec_point_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_ec_point_deinit (struct crypto_ec_point*,int) ; 
 struct crypto_ec_point* crypto_ec_point_init (int /*<<< orphan*/ ) ; 
 scalar_t__ crypto_ec_point_is_at_infinity (int /*<<< orphan*/ ,struct crypto_ec_point*) ; 
 scalar_t__ crypto_ec_point_mul (int /*<<< orphan*/ ,struct crypto_ec_point*,int /*<<< orphan*/ ,struct crypto_ec_point*) ; 
 scalar_t__ crypto_ec_point_x (int /*<<< orphan*/ ,struct crypto_ec_point*,int /*<<< orphan*/ ) ; 
 size_t crypto_ec_prime_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_pwd_get_element (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  eap_pwd_get_scalar (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  eap_pwd_state (struct eap_pwd_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void
eap_pwd_process_commit_resp(struct eap_sm *sm, struct eap_pwd_data *data,
			    const u8 *payload, size_t payload_len)
{
	const u8 *ptr;
	struct crypto_ec_point *K = NULL;
	int res = 0;
	size_t prime_len, order_len;

	wpa_printf(MSG_DEBUG, "EAP-pwd: Received commit response");

	prime_len = crypto_ec_prime_len(data->grp->group);
	order_len = crypto_ec_order_len(data->grp->group);

	if (payload_len != 2 * prime_len + order_len) {
		wpa_printf(MSG_INFO,
			   "EAP-pwd: Unexpected Commit payload length %u (expected %u)",
			   (unsigned int) payload_len,
			   (unsigned int) (2 * prime_len + order_len));
		goto fin;
	}

	data->k = crypto_bignum_init();
	K = crypto_ec_point_init(data->grp->group);
	if (!data->k || !K) {
		wpa_printf(MSG_INFO, "EAP-PWD (server): peer data allocation "
			   "fail");
		goto fin;
	}

	/* element, x then y, followed by scalar */
	ptr = payload;
	data->peer_element = eap_pwd_get_element(data->grp, ptr);
	if (!data->peer_element) {
		wpa_printf(MSG_INFO, "EAP-PWD (server): setting peer element "
			   "fail");
		goto fin;
	}
	ptr += prime_len * 2;
	data->peer_scalar = eap_pwd_get_scalar(data->grp, ptr);
	if (!data->peer_scalar) {
		wpa_printf(MSG_INFO, "EAP-PWD (server): peer data allocation "
			   "fail");
		goto fin;
	}

	/* detect reflection attacks */
	if (crypto_bignum_cmp(data->my_scalar, data->peer_scalar) == 0 ||
	    crypto_ec_point_cmp(data->grp->group, data->my_element,
				data->peer_element) == 0) {
		wpa_printf(MSG_INFO,
			   "EAP-PWD (server): detected reflection attack!");
		goto fin;
	}

	/* compute the shared key, k */
	if ((crypto_ec_point_mul(data->grp->group, data->grp->pwe,
				 data->peer_scalar, K) < 0) ||
	    (crypto_ec_point_add(data->grp->group, K, data->peer_element,
				 K) < 0) ||
	    (crypto_ec_point_mul(data->grp->group, K, data->private_value,
				 K) < 0)) {
		wpa_printf(MSG_INFO, "EAP-PWD (server): computing shared key "
			   "fail");
		goto fin;
	}

	/*
	 * This check is strictly speaking just for the case where
	 * co-factor > 1 but it was suggested that even though this is probably
	 * never going to happen it is a simple and safe check "just to be
	 * sure" so let's be safe.
	 */
	if (crypto_ec_point_is_at_infinity(data->grp->group, K)) {
		wpa_printf(MSG_INFO, "EAP-PWD (server): shared key point is "
			   "at infinity");
		goto fin;
	}
	if (crypto_ec_point_x(data->grp->group, K, data->k)) {
		wpa_printf(MSG_INFO, "EAP-PWD (server): unable to extract "
			   "shared secret from secret point");
		goto fin;
	}
	res = 1;

fin:
	crypto_ec_point_deinit(K, 1);

	if (res)
		eap_pwd_state(data, PWD_Confirm_Req);
	else
		eap_pwd_state(data, FAILURE);
}