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
 int /*<<< orphan*/  AES_GCM_FLAGS ; 
 int /*<<< orphan*/  EVP_CIPHER_impl_ctx_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_CIPHER_meth_free (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * EVP_CIPHER_meth_new (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  EVP_CIPHER_meth_set_ctrl (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_CIPHER_meth_set_do_cipher (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_CIPHER_meth_set_flags (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_CIPHER_meth_set_impl_ctx_size (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_CIPHER_meth_set_init (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_CIPHER_meth_set_iv_length (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  EVP_aes_128_gcm () ; 
 int /*<<< orphan*/  NID_aes_128_gcm ; 
 int /*<<< orphan*/  const* _hidden_aes_128_gcm ; 
 int /*<<< orphan*/  ossltest_aes128_gcm_cipher ; 
 int /*<<< orphan*/  ossltest_aes128_gcm_ctrl ; 
 int /*<<< orphan*/  ossltest_aes128_gcm_init_key ; 

__attribute__((used)) static const EVP_CIPHER *ossltest_aes_128_gcm(void)
{
    if (_hidden_aes_128_gcm == NULL
        && ((_hidden_aes_128_gcm = EVP_CIPHER_meth_new(NID_aes_128_gcm,
                                                       1 /* block size */,
                                                       16 /* key len */)) == NULL
            || !EVP_CIPHER_meth_set_iv_length(_hidden_aes_128_gcm,12)
            || !EVP_CIPHER_meth_set_flags(_hidden_aes_128_gcm, AES_GCM_FLAGS)
            || !EVP_CIPHER_meth_set_init(_hidden_aes_128_gcm,
                                         ossltest_aes128_gcm_init_key)
            || !EVP_CIPHER_meth_set_do_cipher(_hidden_aes_128_gcm,
                                              ossltest_aes128_gcm_cipher)
            || !EVP_CIPHER_meth_set_ctrl(_hidden_aes_128_gcm,
                                              ossltest_aes128_gcm_ctrl)
            || !EVP_CIPHER_meth_set_impl_ctx_size(_hidden_aes_128_gcm,
                              EVP_CIPHER_impl_ctx_size(EVP_aes_128_gcm())))) {
        EVP_CIPHER_meth_free(_hidden_aes_128_gcm);
        _hidden_aes_128_gcm = NULL;
    }
    return _hidden_aes_128_gcm;
}