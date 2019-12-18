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
typedef  int u8 ;
struct dh_group {int /*<<< orphan*/  prime_len; int /*<<< orphan*/  prime; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ crypto_dh_init (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 int eap_eke_dh_generator (int) ; 
 struct dh_group* eap_eke_dh_group (int) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,int*,int /*<<< orphan*/ ) ; 

int eap_eke_dh_init(u8 group, u8 *ret_priv, u8 *ret_pub)
{
	int generator;
	u8 gen;
	const struct dh_group *dh;

	generator = eap_eke_dh_generator(group);
	dh = eap_eke_dh_group(group);
	if (generator < 0 || generator > 255 || !dh)
		return -1;
	gen = generator;

	if (crypto_dh_init(gen, dh->prime, dh->prime_len, ret_priv,
			   ret_pub) < 0)
		return -1;
	wpa_hexdump_key(MSG_DEBUG, "EAP-EKE: DH private value",
			ret_priv, dh->prime_len);
	wpa_hexdump(MSG_DEBUG, "EAP-EKE: DH public value",
		    ret_pub, dh->prime_len);

	return 0;
}