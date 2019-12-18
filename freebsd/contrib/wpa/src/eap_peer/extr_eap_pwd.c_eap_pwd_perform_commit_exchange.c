#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct wpabuf {int dummy; } ;
struct eap_sm {int dummy; } ;
struct eap_pwd_data {scalar_t__ state; int prep; size_t* password; size_t password_len; int /*<<< orphan*/ * outbuf; struct crypto_ec_point* my_element; TYPE_1__* grp; void* my_scalar; void* k; struct crypto_bignum* private_value; int /*<<< orphan*/  server_element; struct crypto_bignum* server_scalar; int /*<<< orphan*/  token; int /*<<< orphan*/  id_peer_len; int /*<<< orphan*/  id_peer; int /*<<< orphan*/  id_server_len; int /*<<< orphan*/  id_server; int /*<<< orphan*/  group_num; int /*<<< orphan*/  password_hash; } ;
struct eap_method_ret {void* ignore; } ;
struct crypto_ec_point {int dummy; } ;
struct crypto_bignum {int dummy; } ;
typedef  int /*<<< orphan*/  salthashpwd ;
typedef  int /*<<< orphan*/  pwhashhash ;
typedef  int /*<<< orphan*/  pwhash ;
struct TYPE_5__ {int /*<<< orphan*/  group; struct crypto_ec_point* pwe; } ;

/* Variables and functions */
#define  EAP_PWD_PREP_MS 132 
#define  EAP_PWD_PREP_NONE 131 
#define  EAP_PWD_PREP_SSHA1 130 
#define  EAP_PWD_PREP_SSHA256 129 
#define  EAP_PWD_PREP_SSHA512 128 
 int /*<<< orphan*/  FAILURE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  MSG_INFO ; 
 scalar_t__ PWD_Commit_Req ; 
 int /*<<< orphan*/  PWD_Confirm_Req ; 
 size_t SHA1_MAC_LEN ; 
 size_t SHA256_MAC_LEN ; 
 size_t SHA512_MAC_LEN ; 
 void* TRUE ; 
 int compute_password_element (TYPE_1__*,int /*<<< orphan*/ ,size_t const*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_bignum_deinit (struct crypto_bignum*,int) ; 
 void* crypto_bignum_init () ; 
 int /*<<< orphan*/  crypto_bignum_to_bin (void*,size_t*,size_t,size_t) ; 
 size_t crypto_ec_order_len (int /*<<< orphan*/ ) ; 
 scalar_t__ crypto_ec_point_add (int /*<<< orphan*/ ,struct crypto_ec_point*,int /*<<< orphan*/ ,struct crypto_ec_point*) ; 
 int /*<<< orphan*/  crypto_ec_point_deinit (struct crypto_ec_point*,int) ; 
 void* crypto_ec_point_init (int /*<<< orphan*/ ) ; 
 scalar_t__ crypto_ec_point_invert (int /*<<< orphan*/ ,struct crypto_ec_point*) ; 
 scalar_t__ crypto_ec_point_is_at_infinity (int /*<<< orphan*/ ,struct crypto_ec_point*) ; 
 scalar_t__ crypto_ec_point_mul (int /*<<< orphan*/ ,struct crypto_ec_point*,struct crypto_bignum*,struct crypto_ec_point*) ; 
 scalar_t__ crypto_ec_point_to_bin (int /*<<< orphan*/ ,struct crypto_ec_point*,size_t*,size_t*) ; 
 scalar_t__ crypto_ec_point_x (int /*<<< orphan*/ ,struct crypto_ec_point*,void*) ; 
 size_t crypto_ec_prime_len (int /*<<< orphan*/ ) ; 
 scalar_t__ crypto_ec_prime_len_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_pwd_get_element (TYPE_1__*,size_t const*) ; 
 scalar_t__ eap_pwd_get_rand_mask (TYPE_1__*,struct crypto_bignum*,struct crypto_bignum*,void*) ; 
 struct crypto_bignum* eap_pwd_get_scalar (TYPE_1__*,size_t const*) ; 
 int /*<<< orphan*/  eap_pwd_state (struct eap_pwd_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  forced_memzero (size_t*,int) ; 
 int hash_nt_password_hash (size_t*,size_t*) ; 
 int nt_password_hash (size_t*,size_t,size_t*) ; 
 int /*<<< orphan*/  sha1_vector (int,size_t const**,size_t*,size_t*) ; 
 int /*<<< orphan*/  sha256_vector (int,size_t const**,size_t*,size_t*) ; 
 int /*<<< orphan*/  sha512_vector (int,size_t const**,size_t*,size_t*) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,size_t const*,size_t) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,size_t const*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * wpabuf_alloc (int) ; 
 size_t* wpabuf_put (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void
eap_pwd_perform_commit_exchange(struct eap_sm *sm, struct eap_pwd_data *data,
				struct eap_method_ret *ret,
				const struct wpabuf *reqData,
				const u8 *payload, size_t payload_len)
{
	struct crypto_ec_point *K = NULL;
	struct crypto_bignum *mask = NULL;
	const u8 *ptr = payload;
	u8 *scalar, *element;
	size_t prime_len, order_len;
	const u8 *password;
	size_t password_len;
	u8 pwhashhash[16];
	const u8 *salt_pwd[2];
	size_t salt_pwd_len[2], exp_len;
	u8 salt_len, salthashpwd[64]; /* 64 = SHA512_DIGEST_LENGTH */
	int res;

	if (data->state != PWD_Commit_Req) {
		ret->ignore = TRUE;
		goto fin;
	}

	if (!data->grp) {
		wpa_printf(MSG_DEBUG,
			   "EAP-PWD (client): uninitialized EAP-pwd group");
		ret->ignore = TRUE;
		goto fin;
	}

	prime_len = crypto_ec_prime_len(data->grp->group);
	order_len = crypto_ec_order_len(data->grp->group);

	switch (data->prep) {
	case EAP_PWD_PREP_MS:
		wpa_printf(MSG_DEBUG,
			   "EAP-pwd commit request, password prep is MS");
#ifdef CONFIG_FIPS
		wpa_printf(MSG_ERROR,
			   "EAP-PWD (peer): MS password hash not supported in FIPS mode");
		eap_pwd_state(data, FAILURE);
		return;
#else /* CONFIG_FIPS */
		if (payload_len != 2 * prime_len + order_len) {
			wpa_printf(MSG_INFO,
				   "EAP-pwd: Unexpected Commit payload length %u (expected %u)",
				   (unsigned int) payload_len,
				   (unsigned int) (2 * prime_len + order_len));
			goto fin;
		}
		if (data->password_hash) {
			res = hash_nt_password_hash(data->password, pwhashhash);
		} else {
			u8 pwhash[16];

			res = nt_password_hash(data->password,
					       data->password_len, pwhash);
			if (res == 0)
				res = hash_nt_password_hash(pwhash, pwhashhash);
			forced_memzero(pwhash, sizeof(pwhash));
		}

		if (res) {
			eap_pwd_state(data, FAILURE);
			return;
		}

		password = pwhashhash;
		password_len = sizeof(pwhashhash);
#endif /* CONFIG_FIPS */
		break;
	case EAP_PWD_PREP_SSHA1:
		wpa_printf(MSG_DEBUG,
			   "EAP-pwd commit request, password prep is salted sha1");
		if (payload_len < 1 || *ptr == 0) {
			wpa_printf(MSG_DEBUG, "EAP-pwd: Invalid Salt-len");
			goto fin;
		}
		salt_len = *ptr++;
		exp_len = 1 + salt_len + 2 * prime_len + order_len;
		if (payload_len != exp_len) {
			wpa_printf(MSG_INFO,
				   "EAP-pwd: Unexpected Commit payload length %u (expected %u)",
				   (unsigned int) payload_len,
				   (unsigned int) exp_len);
			goto fin;
		}

		/* salted-password = Hash(password | salt) */
		wpa_hexdump_key(MSG_DEBUG, "EAP-pwd: Unsalted password",
				data->password, data->password_len);
		wpa_hexdump(MSG_DEBUG, "EAP-pwd: Salt", ptr, salt_len);
		salt_pwd[0] = data->password;
		salt_pwd[1] = ptr;
		salt_pwd_len[0] = data->password_len;
		salt_pwd_len[1] = salt_len;
		if (sha1_vector(2, salt_pwd, salt_pwd_len, salthashpwd) < 0)
			goto fin;

		wpa_printf(MSG_DEBUG,
			   "EAP-pwd: sha1 hashed %d byte salt with password",
			   (int) salt_len);
		ptr += salt_len;
		password = salthashpwd;
		password_len = SHA1_MAC_LEN;
		wpa_hexdump_key(MSG_DEBUG, "EAP-pwd: Salted password",
				password, password_len);
		break;
	case EAP_PWD_PREP_SSHA256:
		wpa_printf(MSG_DEBUG,
			   "EAP-pwd commit request, password prep is salted sha256");
		if (payload_len < 1 || *ptr == 0) {
			wpa_printf(MSG_DEBUG, "EAP-pwd: Invalid Salt-len");
			goto fin;
		}
		salt_len = *ptr++;
		exp_len = 1 + salt_len + 2 * prime_len + order_len;
		if (payload_len != exp_len) {
			wpa_printf(MSG_INFO,
				   "EAP-pwd: Unexpected Commit payload length %u (expected %u)",
				   (unsigned int) payload_len,
				   (unsigned int) exp_len);
			goto fin;
		}

		/* salted-password = Hash(password | salt) */
		wpa_hexdump_key(MSG_DEBUG, "EAP-pwd: Unsalted password",
				data->password, data->password_len);
		wpa_hexdump(MSG_DEBUG, "EAP-pwd: Salt", ptr, salt_len);
		salt_pwd[0] = data->password;
		salt_pwd[1] = ptr;
		salt_pwd_len[0] = data->password_len;
		salt_pwd_len[1] = salt_len;
		if (sha256_vector(2, salt_pwd, salt_pwd_len, salthashpwd) < 0)
			goto fin;

		ptr += salt_len;
		password = salthashpwd;
		password_len = SHA256_MAC_LEN;
		wpa_hexdump_key(MSG_DEBUG, "EAP-pwd: Salted password",
				password, password_len);
		break;
#ifdef CONFIG_SHA512
	case EAP_PWD_PREP_SSHA512:
		wpa_printf(MSG_DEBUG,
			   "EAP-pwd commit request, password prep is salted sha512");
		if (payload_len < 1 || *ptr == 0) {
			wpa_printf(MSG_DEBUG, "EAP-pwd: Invalid Salt-len");
			goto fin;
		}
		salt_len = *ptr++;
		exp_len = 1 + salt_len + 2 * prime_len + order_len;
		if (payload_len != exp_len) {
			wpa_printf(MSG_INFO,
				   "EAP-pwd: Unexpected Commit payload length %u (expected %u)",
				   (unsigned int) payload_len,
				   (unsigned int) exp_len);
			goto fin;
		}

		/* salted-password = Hash(password | salt) */
		wpa_hexdump_key(MSG_DEBUG, "EAP-pwd: Unsalted password",
				data->password, data->password_len);
		wpa_hexdump(MSG_DEBUG, "EAP-pwd: Salt", ptr, salt_len);
		salt_pwd[0] = data->password;
		salt_pwd[1] = ptr;
		salt_pwd_len[0] = data->password_len;
		salt_pwd_len[1] = salt_len;
		if (sha512_vector(2, salt_pwd, salt_pwd_len, salthashpwd) < 0)
			goto fin;

		ptr += salt_len;
		password = salthashpwd;
		password_len = SHA512_MAC_LEN;
		wpa_hexdump_key(MSG_DEBUG, "EAP-pwd: Salted password",
				password, password_len);
		break;
#endif /* CONFIG_SHA512 */
	case EAP_PWD_PREP_NONE:
		wpa_printf(MSG_DEBUG,
			   "EAP-pwd commit request, password prep is NONE");
		if (data->password_hash) {
			wpa_printf(MSG_DEBUG,
				   "EAP-PWD: Unhashed password not available");
			eap_pwd_state(data, FAILURE);
			return;
		}
		if (payload_len != 2 * prime_len + order_len) {
			wpa_printf(MSG_INFO,
				   "EAP-pwd: Unexpected Commit payload length %u (expected %u)",
				   (unsigned int) payload_len,
				   (unsigned int) (2 * prime_len + order_len));
			goto fin;
		}
		password = data->password;
		password_len = data->password_len;
		break;
	default:
		wpa_printf(MSG_DEBUG,
			   "EAP-pwd: Unsupported password pre-processing technique (Prep=%u)",
			   data->prep);
		eap_pwd_state(data, FAILURE);
		return;
	}

	/* compute PWE */
	res = compute_password_element(data->grp, data->group_num,
				       password, password_len,
				       data->id_server, data->id_server_len,
				       data->id_peer, data->id_peer_len,
				       data->token);
	forced_memzero(pwhashhash, sizeof(pwhashhash));
	forced_memzero(salthashpwd, sizeof(salthashpwd));
	if (res) {
		wpa_printf(MSG_INFO, "EAP-PWD (peer): unable to compute PWE");
		eap_pwd_state(data, FAILURE);
		return;
	}

	wpa_printf(MSG_DEBUG, "EAP-PWD (peer): computed %d bit PWE...",
		   (int) crypto_ec_prime_len_bits(data->grp->group));

	data->private_value = crypto_bignum_init();
	data->my_element = crypto_ec_point_init(data->grp->group);
	data->my_scalar = crypto_bignum_init();
	mask = crypto_bignum_init();
	if (!data->private_value || !data->my_element ||
	    !data->my_scalar || !mask) {
		wpa_printf(MSG_INFO, "EAP-PWD (peer): scalar allocation fail");
		goto fin;
	}

	if (eap_pwd_get_rand_mask(data->grp, data->private_value, mask,
				  data->my_scalar) < 0)
		goto fin;

	if (crypto_ec_point_mul(data->grp->group, data->grp->pwe, mask,
				data->my_element) < 0) {
		wpa_printf(MSG_INFO, "EAP-PWD (peer): element allocation "
			   "fail");
		eap_pwd_state(data, FAILURE);
		goto fin;
	}

	if (crypto_ec_point_invert(data->grp->group, data->my_element) < 0) {
		wpa_printf(MSG_INFO, "EAP-PWD (peer): element inversion fail");
		goto fin;
	}

	/* process the request */
	data->k = crypto_bignum_init();
	K = crypto_ec_point_init(data->grp->group);
	if (!data->k || !K) {
		wpa_printf(MSG_INFO, "EAP-PWD (peer): peer data allocation "
			   "fail");
		goto fin;
	}

	/* element, x then y, followed by scalar */
	data->server_element = eap_pwd_get_element(data->grp, ptr);
	if (!data->server_element) {
		wpa_printf(MSG_INFO, "EAP-PWD (peer): setting peer element "
			   "fail");
		goto fin;
	}
	ptr += prime_len * 2;
	data->server_scalar = eap_pwd_get_scalar(data->grp, ptr);
	if (!data->server_scalar) {
		wpa_printf(MSG_INFO,
			   "EAP-PWD (peer): setting peer scalar fail");
		goto fin;
	}

	/* compute the shared key, k */
	if (crypto_ec_point_mul(data->grp->group, data->grp->pwe,
				data->server_scalar, K) < 0 ||
	    crypto_ec_point_add(data->grp->group, K, data->server_element,
				K) < 0 ||
	    crypto_ec_point_mul(data->grp->group, K, data->private_value,
				K) < 0) {
		wpa_printf(MSG_INFO, "EAP-PWD (peer): computing shared key "
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
		wpa_printf(MSG_INFO, "EAP-PWD (peer): shared key point is at "
			   "infinity!\n");
		goto fin;
	}

	if (crypto_ec_point_x(data->grp->group, K, data->k) < 0) {
		wpa_printf(MSG_INFO, "EAP-PWD (peer): unable to extract "
			   "shared secret from point");
		goto fin;
	}

	/* now do the response */
	data->outbuf = wpabuf_alloc(2 * prime_len + order_len);
	if (data->outbuf == NULL)
		goto fin;
	/* We send the element as (x,y) followed by the scalar */
	element = wpabuf_put(data->outbuf, 2 * prime_len);
	scalar = wpabuf_put(data->outbuf, order_len);

	/*
	 * bignums occupy as little memory as possible so one that is
	 * sufficiently smaller than the prime or order might need pre-pending
	 * with zeros.
	 */
	crypto_bignum_to_bin(data->my_scalar, scalar, order_len, order_len);
	if (crypto_ec_point_to_bin(data->grp->group, data->my_element, element,
				   element + prime_len) != 0) {
		wpa_printf(MSG_INFO, "EAP-PWD (peer): point assignment fail");
		goto fin;
	}

fin:
	crypto_bignum_deinit(mask, 1);
	crypto_ec_point_deinit(K, 1);
	if (data->outbuf == NULL)
		eap_pwd_state(data, FAILURE);
	else
		eap_pwd_state(data, PWD_Confirm_Req);
}