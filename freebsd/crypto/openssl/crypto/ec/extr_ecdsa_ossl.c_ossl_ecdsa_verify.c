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
typedef  int /*<<< orphan*/  EC_KEY ;
typedef  int /*<<< orphan*/  ECDSA_SIG ;

/* Variables and functions */
 int /*<<< orphan*/  ECDSA_SIG_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ECDSA_SIG_new () ; 
 int ECDSA_do_verify (unsigned char const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPENSSL_clear_free (unsigned char*,int) ; 
 int /*<<< orphan*/ * d2i_ECDSA_SIG (int /*<<< orphan*/ **,unsigned char const**,int) ; 
 int i2d_ECDSA_SIG (int /*<<< orphan*/ *,unsigned char**) ; 
 scalar_t__ memcmp (unsigned char const*,unsigned char*,int) ; 

int ossl_ecdsa_verify(int type, const unsigned char *dgst, int dgst_len,
                      const unsigned char *sigbuf, int sig_len, EC_KEY *eckey)
{
    ECDSA_SIG *s;
    const unsigned char *p = sigbuf;
    unsigned char *der = NULL;
    int derlen = -1;
    int ret = -1;

    s = ECDSA_SIG_new();
    if (s == NULL)
        return ret;
    if (d2i_ECDSA_SIG(&s, &p, sig_len) == NULL)
        goto err;
    /* Ensure signature uses DER and doesn't have trailing garbage */
    derlen = i2d_ECDSA_SIG(s, &der);
    if (derlen != sig_len || memcmp(sigbuf, der, derlen) != 0)
        goto err;
    ret = ECDSA_do_verify(dgst, dgst_len, s, eckey);
 err:
    OPENSSL_clear_free(der, derlen);
    ECDSA_SIG_free(s);
    return ret;
}