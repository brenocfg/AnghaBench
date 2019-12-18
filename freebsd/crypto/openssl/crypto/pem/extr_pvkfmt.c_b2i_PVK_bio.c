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
typedef  int /*<<< orphan*/  pem_password_cb ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int BIO_read (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_clear_free (unsigned char*,int) ; 
 unsigned char* OPENSSL_malloc (int) ; 
 int /*<<< orphan*/  PEM_F_B2I_PVK_BIO ; 
 int /*<<< orphan*/  PEM_R_PVK_DATA_TOO_SHORT ; 
 int /*<<< orphan*/  PEMerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * do_PVK_body (unsigned char const**,unsigned int,unsigned int,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  do_PVK_header (unsigned char const**,int,int /*<<< orphan*/ ,unsigned int*,unsigned int*) ; 

EVP_PKEY *b2i_PVK_bio(BIO *in, pem_password_cb *cb, void *u)
{
    unsigned char pvk_hdr[24], *buf = NULL;
    const unsigned char *p;
    int buflen;
    EVP_PKEY *ret = NULL;
    unsigned int saltlen, keylen;
    if (BIO_read(in, pvk_hdr, 24) != 24) {
        PEMerr(PEM_F_B2I_PVK_BIO, PEM_R_PVK_DATA_TOO_SHORT);
        return NULL;
    }
    p = pvk_hdr;

    if (!do_PVK_header(&p, 24, 0, &saltlen, &keylen))
        return 0;
    buflen = (int)keylen + saltlen;
    buf = OPENSSL_malloc(buflen);
    if (buf == NULL) {
        PEMerr(PEM_F_B2I_PVK_BIO, ERR_R_MALLOC_FAILURE);
        return 0;
    }
    p = buf;
    if (BIO_read(in, buf, buflen) != buflen) {
        PEMerr(PEM_F_B2I_PVK_BIO, PEM_R_PVK_DATA_TOO_SHORT);
        goto err;
    }
    ret = do_PVK_body(&p, saltlen, keylen, cb, u);

 err:
    OPENSSL_clear_free(buf, buflen);
    return ret;
}