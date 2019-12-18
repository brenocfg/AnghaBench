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
typedef  int /*<<< orphan*/  EVP_CIPHER ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_CIPHER_impl_ctx_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_CIPHER_meth_free (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * EVP_CIPHER_meth_new (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  EVP_CIPHER_meth_set_do_cipher (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_CIPHER_meth_set_flags (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  EVP_CIPHER_meth_set_impl_ctx_size (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_CIPHER_meth_set_init (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_CIPHER_meth_set_iv_length (int /*<<< orphan*/  const*,int) ; 
 int EVP_CIPH_CBC_MODE ; 
 int EVP_CIPH_FLAG_DEFAULT_ASN1 ; 
 int /*<<< orphan*/  EVP_aes_128_cbc () ; 
 int /*<<< orphan*/  NID_aes_128_cbc ; 
 int /*<<< orphan*/  const* _hidden_aes_128_cbc ; 
 int /*<<< orphan*/  ossltest_aes128_cbc_cipher ; 
 int /*<<< orphan*/  ossltest_aes128_init_key ; 

__attribute__((used)) static const EVP_CIPHER *ossltest_aes_128_cbc(void)
{
    if (_hidden_aes_128_cbc == NULL
        && ((_hidden_aes_128_cbc = EVP_CIPHER_meth_new(NID_aes_128_cbc,
                                                       16 /* block size */,
                                                       16 /* key len */)) == NULL
            || !EVP_CIPHER_meth_set_iv_length(_hidden_aes_128_cbc,16)
            || !EVP_CIPHER_meth_set_flags(_hidden_aes_128_cbc,
                                          EVP_CIPH_FLAG_DEFAULT_ASN1
                                          | EVP_CIPH_CBC_MODE)
            || !EVP_CIPHER_meth_set_init(_hidden_aes_128_cbc,
                                         ossltest_aes128_init_key)
            || !EVP_CIPHER_meth_set_do_cipher(_hidden_aes_128_cbc,
                                              ossltest_aes128_cbc_cipher)
            || !EVP_CIPHER_meth_set_impl_ctx_size(_hidden_aes_128_cbc,
                                                  EVP_CIPHER_impl_ctx_size(EVP_aes_128_cbc())))) {
        EVP_CIPHER_meth_free(_hidden_aes_128_cbc);
        _hidden_aes_128_cbc = NULL;
    }
    return _hidden_aes_128_cbc;
}