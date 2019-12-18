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
struct dpp_authentication {int /*<<< orphan*/  net_access_key; int /*<<< orphan*/  own_protocol_key; } ;
typedef  int /*<<< orphan*/  EC_KEY ;

/* Variables and functions */
 int /*<<< orphan*/  EC_KEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_get1_EC_KEY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 int i2d_ECPrivateKey (int /*<<< orphan*/ *,unsigned char**) ; 
 int /*<<< orphan*/  wpabuf_alloc_copy (unsigned char*,int) ; 
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dpp_copy_netaccesskey(struct dpp_authentication *auth)
{
	unsigned char *der = NULL;
	int der_len;
	EC_KEY *eckey;

	eckey = EVP_PKEY_get1_EC_KEY(auth->own_protocol_key);
	if (!eckey)
		return;

	der_len = i2d_ECPrivateKey(eckey, &der);
	if (der_len <= 0) {
		EC_KEY_free(eckey);
		return;
	}
	wpabuf_free(auth->net_access_key);
	auth->net_access_key = wpabuf_alloc_copy(der, der_len);
	OPENSSL_free(der);
	EC_KEY_free(eckey);
}