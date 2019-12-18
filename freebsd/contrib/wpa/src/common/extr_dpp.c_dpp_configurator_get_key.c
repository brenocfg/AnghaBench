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
struct dpp_configurator {int /*<<< orphan*/  csign; } ;
typedef  int /*<<< orphan*/  EC_KEY ;

/* Variables and functions */
 int /*<<< orphan*/  EC_KEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_get1_EC_KEY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 int i2d_ECPrivateKey (int /*<<< orphan*/ *,unsigned char**) ; 
 int wpa_snprintf_hex (char*,size_t,unsigned char*,int) ; 

int dpp_configurator_get_key(const struct dpp_configurator *conf, char *buf,
			     size_t buflen)
{
	EC_KEY *eckey;
	int key_len, ret = -1;
	unsigned char *key = NULL;

	if (!conf->csign)
		return -1;

	eckey = EVP_PKEY_get1_EC_KEY(conf->csign);
	if (!eckey)
		return -1;

	key_len = i2d_ECPrivateKey(eckey, &key);
	if (key_len > 0)
		ret = wpa_snprintf_hex(buf, buflen, key, key_len);

	EC_KEY_free(eckey);
	OPENSSL_free(key);
	return ret;
}