#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int flags; int /*<<< orphan*/ * n; int /*<<< orphan*/  _method_mod_n; int /*<<< orphan*/ * e; TYPE_1__* meth; int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* bn_mod_exp ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ RSA ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 int /*<<< orphan*/  BN_CTX_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_MONT_CTX_set_locked (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_bin2bn (unsigned char const*,int,int /*<<< orphan*/ *) ; 
 int BN_bn2binpad (int /*<<< orphan*/ *,unsigned char*,int) ; 
 scalar_t__ BN_num_bits (int /*<<< orphan*/ *) ; 
 int BN_num_bytes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_sub (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ BN_ucmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 scalar_t__ OPENSSL_RSA_MAX_MODULUS_BITS ; 
 scalar_t__ OPENSSL_RSA_MAX_PUBEXP_BITS ; 
 scalar_t__ OPENSSL_RSA_SMALL_MODULUS_BITS ; 
 int /*<<< orphan*/  OPENSSL_clear_free (unsigned char*,int) ; 
 unsigned char* OPENSSL_malloc (int) ; 
 int RSA_FLAG_CACHE_PUBLIC ; 
 int /*<<< orphan*/  RSA_F_RSA_OSSL_PUBLIC_DECRYPT ; 
#define  RSA_NO_PADDING 130 
#define  RSA_PKCS1_PADDING 129 
 int /*<<< orphan*/  RSA_R_BAD_E_VALUE ; 
 int /*<<< orphan*/  RSA_R_DATA_GREATER_THAN_MOD_LEN ; 
 int /*<<< orphan*/  RSA_R_DATA_TOO_LARGE_FOR_MODULUS ; 
 int /*<<< orphan*/  RSA_R_MODULUS_TOO_LARGE ; 
 int /*<<< orphan*/  RSA_R_PADDING_CHECK_FAILED ; 
 int /*<<< orphan*/  RSA_R_UNKNOWN_PADDING_TYPE ; 
#define  RSA_X931_PADDING 128 
 int RSA_padding_check_PKCS1_type_1 (unsigned char*,int,unsigned char*,int,int) ; 
 int RSA_padding_check_X931 (unsigned char*,int,unsigned char*,int,int) ; 
 int /*<<< orphan*/  RSAerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int* bn_get_words (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rsa_ossl_public_decrypt(int flen, const unsigned char *from,
                                  unsigned char *to, RSA *rsa, int padding)
{
    BIGNUM *f, *ret;
    int i, num = 0, r = -1;
    unsigned char *buf = NULL;
    BN_CTX *ctx = NULL;

    if (BN_num_bits(rsa->n) > OPENSSL_RSA_MAX_MODULUS_BITS) {
        RSAerr(RSA_F_RSA_OSSL_PUBLIC_DECRYPT, RSA_R_MODULUS_TOO_LARGE);
        return -1;
    }

    if (BN_ucmp(rsa->n, rsa->e) <= 0) {
        RSAerr(RSA_F_RSA_OSSL_PUBLIC_DECRYPT, RSA_R_BAD_E_VALUE);
        return -1;
    }

    /* for large moduli, enforce exponent limit */
    if (BN_num_bits(rsa->n) > OPENSSL_RSA_SMALL_MODULUS_BITS) {
        if (BN_num_bits(rsa->e) > OPENSSL_RSA_MAX_PUBEXP_BITS) {
            RSAerr(RSA_F_RSA_OSSL_PUBLIC_DECRYPT, RSA_R_BAD_E_VALUE);
            return -1;
        }
    }

    if ((ctx = BN_CTX_new()) == NULL)
        goto err;
    BN_CTX_start(ctx);
    f = BN_CTX_get(ctx);
    ret = BN_CTX_get(ctx);
    num = BN_num_bytes(rsa->n);
    buf = OPENSSL_malloc(num);
    if (ret == NULL || buf == NULL) {
        RSAerr(RSA_F_RSA_OSSL_PUBLIC_DECRYPT, ERR_R_MALLOC_FAILURE);
        goto err;
    }

    /*
     * This check was for equality but PGP does evil things and chops off the
     * top '0' bytes
     */
    if (flen > num) {
        RSAerr(RSA_F_RSA_OSSL_PUBLIC_DECRYPT, RSA_R_DATA_GREATER_THAN_MOD_LEN);
        goto err;
    }

    if (BN_bin2bn(from, flen, f) == NULL)
        goto err;

    if (BN_ucmp(f, rsa->n) >= 0) {
        RSAerr(RSA_F_RSA_OSSL_PUBLIC_DECRYPT,
               RSA_R_DATA_TOO_LARGE_FOR_MODULUS);
        goto err;
    }

    if (rsa->flags & RSA_FLAG_CACHE_PUBLIC)
        if (!BN_MONT_CTX_set_locked(&rsa->_method_mod_n, rsa->lock,
                                    rsa->n, ctx))
            goto err;

    if (!rsa->meth->bn_mod_exp(ret, f, rsa->e, rsa->n, ctx,
                               rsa->_method_mod_n))
        goto err;

    if ((padding == RSA_X931_PADDING) && ((bn_get_words(ret)[0] & 0xf) != 12))
        if (!BN_sub(ret, rsa->n, ret))
            goto err;

    i = BN_bn2binpad(ret, buf, num);

    switch (padding) {
    case RSA_PKCS1_PADDING:
        r = RSA_padding_check_PKCS1_type_1(to, num, buf, i, num);
        break;
    case RSA_X931_PADDING:
        r = RSA_padding_check_X931(to, num, buf, i, num);
        break;
    case RSA_NO_PADDING:
        memcpy(to, buf, (r = i));
        break;
    default:
        RSAerr(RSA_F_RSA_OSSL_PUBLIC_DECRYPT, RSA_R_UNKNOWN_PADDING_TYPE);
        goto err;
    }
    if (r < 0)
        RSAerr(RSA_F_RSA_OSSL_PUBLIC_DECRYPT, RSA_R_PADDING_CHECK_FAILED);

 err:
    BN_CTX_end(ctx);
    BN_CTX_free(ctx);
    OPENSSL_clear_free(buf, num);
    return r;
}