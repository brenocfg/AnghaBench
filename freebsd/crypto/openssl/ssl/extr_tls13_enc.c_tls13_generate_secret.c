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
typedef  int /*<<< orphan*/  derived_secret_label ;
typedef  int /*<<< orphan*/  SSL ;
typedef  int /*<<< orphan*/  EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 scalar_t__ EVP_DigestFinal_ex (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_DigestInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int EVP_MAX_MD_SIZE ; 
 int /*<<< orphan*/  EVP_MD_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_new () ; 
 int EVP_MD_size (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EVP_PKEY_CTX_free (int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_PKEY_CTX_hkdf_mode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * EVP_PKEY_CTX_new_id (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_PKEY_CTX_set1_hkdf_key (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 
 scalar_t__ EVP_PKEY_CTX_set1_hkdf_salt (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 
 scalar_t__ EVP_PKEY_CTX_set_hkdf_md (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EVP_PKEY_HKDEF_MODE_EXTRACT_ONLY ; 
 int /*<<< orphan*/  EVP_PKEY_HKDF ; 
 scalar_t__ EVP_PKEY_derive (int /*<<< orphan*/ *,unsigned char*,size_t*) ; 
 scalar_t__ EVP_PKEY_derive_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPENSSL_cleanse (unsigned char*,size_t) ; 
 int /*<<< orphan*/  SSL_AD_INTERNAL_ERROR ; 
 int /*<<< orphan*/  SSL_F_TLS13_GENERATE_SECRET ; 
 int /*<<< orphan*/  SSLfatal (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned char* default_zeros ; 
 int /*<<< orphan*/  ossl_assert (int) ; 
 int /*<<< orphan*/  tls13_hkdf_expand (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned char const*,unsigned char*,int,unsigned char*,size_t,unsigned char*,size_t,int) ; 

int tls13_generate_secret(SSL *s, const EVP_MD *md,
                          const unsigned char *prevsecret,
                          const unsigned char *insecret,
                          size_t insecretlen,
                          unsigned char *outsecret)
{
    size_t mdlen, prevsecretlen;
    int mdleni;
    int ret;
    EVP_PKEY_CTX *pctx = EVP_PKEY_CTX_new_id(EVP_PKEY_HKDF, NULL);
#ifdef CHARSET_EBCDIC
    static const char derived_secret_label[] = { 0x64, 0x65, 0x72, 0x69, 0x76, 0x65, 0x64, 0x00 };
#else
    static const char derived_secret_label[] = "derived";
#endif
    unsigned char preextractsec[EVP_MAX_MD_SIZE];

    if (pctx == NULL) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS13_GENERATE_SECRET,
                 ERR_R_INTERNAL_ERROR);
        return 0;
    }

    mdleni = EVP_MD_size(md);
    /* Ensure cast to size_t is safe */
    if (!ossl_assert(mdleni >= 0)) {
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS13_GENERATE_SECRET,
                 ERR_R_INTERNAL_ERROR);
        return 0;
    }
    mdlen = (size_t)mdleni;

    if (insecret == NULL) {
        insecret = default_zeros;
        insecretlen = mdlen;
    }
    if (prevsecret == NULL) {
        prevsecret = default_zeros;
        prevsecretlen = 0;
    } else {
        EVP_MD_CTX *mctx = EVP_MD_CTX_new();
        unsigned char hash[EVP_MAX_MD_SIZE];

        /* The pre-extract derive step uses a hash of no messages */
        if (mctx == NULL
                || EVP_DigestInit_ex(mctx, md, NULL) <= 0
                || EVP_DigestFinal_ex(mctx, hash, NULL) <= 0) {
            SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS13_GENERATE_SECRET,
                     ERR_R_INTERNAL_ERROR);
            EVP_MD_CTX_free(mctx);
            EVP_PKEY_CTX_free(pctx);
            return 0;
        }
        EVP_MD_CTX_free(mctx);

        /* Generate the pre-extract secret */
        if (!tls13_hkdf_expand(s, md, prevsecret,
                               (unsigned char *)derived_secret_label,
                               sizeof(derived_secret_label) - 1, hash, mdlen,
                               preextractsec, mdlen, 1)) {
            /* SSLfatal() already called */
            EVP_PKEY_CTX_free(pctx);
            return 0;
        }

        prevsecret = preextractsec;
        prevsecretlen = mdlen;
    }

    ret = EVP_PKEY_derive_init(pctx) <= 0
            || EVP_PKEY_CTX_hkdf_mode(pctx, EVP_PKEY_HKDEF_MODE_EXTRACT_ONLY)
               <= 0
            || EVP_PKEY_CTX_set_hkdf_md(pctx, md) <= 0
            || EVP_PKEY_CTX_set1_hkdf_key(pctx, insecret, insecretlen) <= 0
            || EVP_PKEY_CTX_set1_hkdf_salt(pctx, prevsecret, prevsecretlen)
               <= 0
            || EVP_PKEY_derive(pctx, outsecret, &mdlen)
               <= 0;

    if (ret != 0)
        SSLfatal(s, SSL_AD_INTERNAL_ERROR, SSL_F_TLS13_GENERATE_SECRET,
                 ERR_R_INTERNAL_ERROR);

    EVP_PKEY_CTX_free(pctx);
    if (prevsecret == preextractsec)
        OPENSSL_cleanse(preextractsec, mdlen);
    return ret == 0;
}