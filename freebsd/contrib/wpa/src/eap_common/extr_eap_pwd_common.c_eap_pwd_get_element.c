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
struct crypto_ec_point {int dummy; } ;
struct crypto_bignum {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  group; } ;
typedef  TYPE_1__ EAP_PWD_group ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_INFO ; 
 struct crypto_bignum* crypto_ec_get_prime (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_ec_point_deinit (struct crypto_ec_point*,int /*<<< orphan*/ ) ; 
 struct crypto_ec_point* crypto_ec_point_from_bin (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 scalar_t__ crypto_ec_point_is_at_infinity (int /*<<< orphan*/ ,struct crypto_ec_point*) ; 
 int /*<<< orphan*/  crypto_ec_point_is_on_curve (int /*<<< orphan*/ ,struct crypto_ec_point*) ; 
 size_t crypto_ec_prime_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_pwd_element_coord_ok (struct crypto_bignum const*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

struct crypto_ec_point * eap_pwd_get_element(EAP_PWD_group *group,
					     const u8 *buf)
{
	struct crypto_ec_point *element;
	const struct crypto_bignum *prime;
	size_t prime_len;

	prime = crypto_ec_get_prime(group->group);
	prime_len = crypto_ec_prime_len(group->group);

	/* RFC 5931, 2.8.5.2.2: 0 < x,y < p */
	if (!eap_pwd_element_coord_ok(prime, buf, prime_len) ||
	    !eap_pwd_element_coord_ok(prime, buf + prime_len, prime_len)) {
		wpa_printf(MSG_INFO, "EAP-pwd: Invalid coordinate in element");
		return NULL;
	}

	element = crypto_ec_point_from_bin(group->group, buf);
	if (!element) {
		wpa_printf(MSG_INFO, "EAP-pwd: EC point from element failed");
		return NULL;
	}

	/* RFC 5931, 2.8.5.2.2: on curve and not the point at infinity */
	if (!crypto_ec_point_is_on_curve(group->group, element) ||
	    crypto_ec_point_is_at_infinity(group->group, element)) {
		wpa_printf(MSG_INFO, "EAP-pwd: Invalid element");
		goto fail;
	}

out:
	return element;
fail:
	crypto_ec_point_deinit(element, 0);
	element = NULL;
	goto out;
}