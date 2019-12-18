#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  key ;
struct TYPE_17__ {TYPE_5__* s3; TYPE_2__* session; } ;
struct TYPE_15__ {TYPE_3__* new_cipher; } ;
struct TYPE_16__ {TYPE_4__ tmp; } ;
struct TYPE_14__ {int algorithm_enc; } ;
struct TYPE_13__ {TYPE_1__* cipher; } ;
struct TYPE_12__ {int algorithm_enc; } ;
typedef  TYPE_6__ SSL ;
typedef  int /*<<< orphan*/  EVP_MD ;
typedef  int /*<<< orphan*/  EVP_CIPHER_CTX ;
typedef  int /*<<< orphan*/  EVP_CIPHER ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_EVP_LIB ; 
 size_t EVP_CCM8_TLS_TAG_LEN ; 
 size_t EVP_CCM_TLS_IV_LEN ; 
 size_t EVP_CCM_TLS_TAG_LEN ; 
 int /*<<< orphan*/  EVP_CIPHER_CTX_ctrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *) ; 
 size_t EVP_CIPHER_iv_length (int /*<<< orphan*/  const*) ; 
 size_t EVP_CIPHER_key_length (int /*<<< orphan*/  const*) ; 
 scalar_t__ EVP_CIPHER_mode (int /*<<< orphan*/  const*) ; 
 scalar_t__ EVP_CIPH_CCM_MODE ; 
 int /*<<< orphan*/  EVP_CTRL_AEAD_SET_IVLEN ; 
 int /*<<< orphan*/  EVP_CTRL_AEAD_SET_TAG ; 
 scalar_t__ EVP_CipherInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ *,int) ; 
 int EVP_MAX_KEY_LENGTH ; 
 int EVP_MD_size (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  OPENSSL_cleanse (unsigned char*,int) ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int SSL_AES128CCM8 ; 
 int SSL_AES256CCM8 ; 
 int /*<<< orphan*/  SSL_F_DERIVE_SECRET_KEY_AND_IV ; 
 int /*<<< orphan*/  SSLfatal (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ossl_assert (int) ; 
 int /*<<< orphan*/  tls13_derive_iv (TYPE_6__*,int /*<<< orphan*/  const*,unsigned char*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  tls13_derive_key (TYPE_6__*,int /*<<< orphan*/  const*,unsigned char*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  tls13_hkdf_expand (TYPE_6__*,int /*<<< orphan*/  const*,unsigned char const*,unsigned char const*,size_t,unsigned char const*,size_t,unsigned char*,size_t,int) ; 

__attribute__((used)) static int derive_secret_key_and_iv(SSL *s, int sending, const EVP_MD *md,
                                    const EVP_CIPHER *ciph,
                                    const unsigned char *insecret,
                                    const unsigned char *hash,
                                    const unsigned char *label,
                                    size_t labellen, unsigned char *secret,
                                    unsigned char *iv, EVP_CIPHER_CTX *ciph_ctx)
{
    unsigned char key[EVP_MAX_KEY_LENGTH];
    size_t ivlen, keylen, taglen;
    int hashleni = EVP_MD_size(md);
    size_t hashlen;

    /* Ensure cast to size_t is safe */
    if (!ossl_assert(hashleni >= 0)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_DERIVE_SECRET_KEY_AND_IV,
                 ERR_R_EVP_LIB);
        goto err;
    }
    hashlen = (size_t)hashleni;

    if (!tls13_hkdf_expand(s, md, insecret, label, labellen, hash, hashlen,
                           secret, hashlen, 1)) {
        /* SSLfatal() already called */
        goto err;
    }

    /* TODO(size_t): convert me */
    keylen = EVP_CIPHER_key_length(ciph);
    if (EVP_CIPHER_mode(ciph) == EVP_CIPH_CCM_MODE) {
        uint32_t algenc;

        ivlen = EVP_CCM_TLS_IV_LEN;
        if (s->s3->tmp.new_cipher == NULL) {
            /* We've not selected a cipher yet - we must be doing early data */
            algenc = s->session->cipher->algorithm_enc;
        } else {
            algenc = s->s3->tmp.new_cipher->algorithm_enc;
        }
        if (algenc & (SSL_AES128CCM8 | SSL_AES256CCM8))
            taglen = EVP_CCM8_TLS_TAG_LEN;
         else
            taglen = EVP_CCM_TLS_TAG_LEN;
    } else {
        ivlen = EVP_CIPHER_iv_length(ciph);
        taglen = 0;
    }

    if (!tls13_derive_key(s, md, secret, key, keylen)
            || !tls13_derive_iv(s, md, secret, iv, ivlen)) {
        /* SSLfatal() already called */
        goto err;
    }

    if (EVP_CipherInit_ex(ciph_ctx, ciph, NULL, NULL, NULL, sending) <= 0
        || !EVP_CIPHER_CTX_ctrl(ciph_ctx, EVP_CTRL_AEAD_SET_IVLEN, ivlen, NULL)
        || (taglen != 0 && !EVP_CIPHER_CTX_ctrl(ciph_ctx, EVP_CTRL_AEAD_SET_TAG,
                                                taglen, NULL))
        || EVP_CipherInit_ex(ciph_ctx, NULL, NULL, key, NULL, -1) <= 0) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_DERIVE_SECRET_KEY_AND_IV,
                 ERR_R_EVP_LIB);
        goto err;
    }

    return 1;
 err:
    OPENSSL_cleanse(key, sizeof(key));
    return 0;
}