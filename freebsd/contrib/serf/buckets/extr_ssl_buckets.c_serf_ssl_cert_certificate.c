#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  ssl_cert; } ;
typedef  TYPE_1__ serf_ssl_certificate_t ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;
typedef  int /*<<< orphan*/  BIO ;
typedef  int /*<<< orphan*/  ASN1_TIME ;

/* Variables and functions */
 int /*<<< orphan*/  APR_HASH_KEY_STRING ; 
 scalar_t__ ASN1_TIME_print (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_read (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  BIO_s_mem () ; 
 int EVP_MAX_MD_SIZE ; 
 int /*<<< orphan*/  EVP_sha1 () ; 
 int /*<<< orphan*/  EscapeNulAndCopy ; 
 scalar_t__ X509_digest (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,unsigned int*) ; 
 int /*<<< orphan*/ * X509_get_notAfter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * X509_get_notBefore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_set (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_pstrdup (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  get_subject_alt_names (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 

apr_hash_t *serf_ssl_cert_certificate(
    const serf_ssl_certificate_t *cert,
    apr_pool_t *pool)
{
    apr_hash_t *tgt = apr_hash_make(pool);
    unsigned int md_size, i;
    unsigned char md[EVP_MAX_MD_SIZE];
    BIO *bio;
    apr_array_header_t *san_arr;

    /* sha1 fingerprint */
    if (X509_digest(cert->ssl_cert, EVP_sha1(), md, &md_size)) {
        const char hex[] = "0123456789ABCDEF";
        char fingerprint[EVP_MAX_MD_SIZE * 3];

        for (i=0; i<md_size; i++) {
            fingerprint[3*i] = hex[(md[i] & 0xf0) >> 4];
            fingerprint[(3*i)+1] = hex[(md[i] & 0x0f)];
            fingerprint[(3*i)+2] = ':';
        }
        if (md_size > 0)
            fingerprint[(3*(md_size-1))+2] = '\0';
        else
            fingerprint[0] = '\0';

        apr_hash_set(tgt, "sha1", APR_HASH_KEY_STRING,
                     apr_pstrdup(pool, fingerprint));
    }

    /* set expiry dates */
    bio = BIO_new(BIO_s_mem());
    if (bio) {
        ASN1_TIME *notBefore, *notAfter;
        char buf[256];

        memset (buf, 0, sizeof (buf));
        notBefore = X509_get_notBefore(cert->ssl_cert);
        if (ASN1_TIME_print(bio, notBefore)) {
            BIO_read(bio, buf, 255);
            apr_hash_set(tgt, "notBefore", APR_HASH_KEY_STRING,
                         apr_pstrdup(pool, buf));
        }
        memset (buf, 0, sizeof (buf));
        notAfter = X509_get_notAfter(cert->ssl_cert);
        if (ASN1_TIME_print(bio, notAfter)) {
            BIO_read(bio, buf, 255);
            apr_hash_set(tgt, "notAfter", APR_HASH_KEY_STRING,
                         apr_pstrdup(pool, buf));
        }
    }
    BIO_free(bio);

    /* Get subjectAltNames */
    if (!get_subject_alt_names(&san_arr, cert->ssl_cert, EscapeNulAndCopy, pool))
        apr_hash_set(tgt, "subjectAltName", APR_HASH_KEY_STRING, san_arr);

    return tgt;
}