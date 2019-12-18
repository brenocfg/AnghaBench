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
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 char* BN_bn2dec (int /*<<< orphan*/  const*) ; 
 char* BN_bn2hex (int /*<<< orphan*/  const*) ; 
 int BN_num_bits (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 char* OPENSSL_malloc (size_t) ; 
 int /*<<< orphan*/  OPENSSL_strlcat (char*,char*,size_t) ; 
 int /*<<< orphan*/  OPENSSL_strlcpy (char*,char*,size_t) ; 
 int /*<<< orphan*/  X509V3_F_BIGNUM_TO_STRING ; 
 int /*<<< orphan*/  X509V3err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 

__attribute__((used)) static char *bignum_to_string(const BIGNUM *bn)
{
    char *tmp, *ret;
    size_t len;

    /*
     * Display large numbers in hex and small numbers in decimal. Converting to
     * decimal takes quadratic time and is no more useful than hex for large
     * numbers.
     */
    if (BN_num_bits(bn) < 128)
        return BN_bn2dec(bn);

    tmp = BN_bn2hex(bn);
    if (tmp == NULL)
        return NULL;

    len = strlen(tmp) + 3;
    ret = OPENSSL_malloc(len);
    if (ret == NULL) {
        X509V3err(X509V3_F_BIGNUM_TO_STRING, ERR_R_MALLOC_FAILURE);
        OPENSSL_free(tmp);
        return NULL;
    }

    /* Prepend "0x", but place it after the "-" if negative. */
    if (tmp[0] == '-') {
        OPENSSL_strlcpy(ret, "-0x", len);
        OPENSSL_strlcat(ret, tmp + 1, len);
    } else {
        OPENSSL_strlcpy(ret, "0x", len);
        OPENSSL_strlcat(ret, tmp, len);
    }
    OPENSSL_free(tmp);
    return ret;
}