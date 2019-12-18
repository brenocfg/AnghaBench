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
struct dpp_authentication {int /*<<< orphan*/  c_sign_key; } ;
typedef  int /*<<< orphan*/  EVP_PKEY ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 int i2d_PUBKEY (int /*<<< orphan*/ *,unsigned char**) ; 
 int /*<<< orphan*/  wpabuf_alloc_copy (unsigned char*,int) ; 
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dpp_copy_csign(struct dpp_authentication *auth, EVP_PKEY *csign)
{
	unsigned char *der = NULL;
	int der_len;

	der_len = i2d_PUBKEY(csign, &der);
	if (der_len <= 0)
		return;
	wpabuf_free(auth->c_sign_key);
	auth->c_sign_key = wpabuf_alloc_copy(der, der_len);
	OPENSSL_free(der);
}