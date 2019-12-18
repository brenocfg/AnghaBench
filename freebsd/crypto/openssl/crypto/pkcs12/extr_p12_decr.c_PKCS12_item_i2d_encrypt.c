#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509_ALGOR ;
struct TYPE_5__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ ASN1_OCTET_STRING ;
typedef  int /*<<< orphan*/  ASN1_ITEM ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_OCTET_STRING_free (TYPE_1__*) ; 
 TYPE_1__* ASN1_OCTET_STRING_new () ; 
 int ASN1_item_i2d (void*,unsigned char**,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_cleanse (unsigned char*,int) ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 int /*<<< orphan*/  PKCS12_F_PKCS12_ITEM_I2D_ENCRYPT ; 
 int /*<<< orphan*/  PKCS12_R_ENCODE_ERROR ; 
 int /*<<< orphan*/  PKCS12_R_ENCRYPT_ERROR ; 
 int /*<<< orphan*/  PKCS12_pbe_crypt (int /*<<< orphan*/ *,char const*,int,unsigned char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  PKCS12err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ASN1_OCTET_STRING *PKCS12_item_i2d_encrypt(X509_ALGOR *algor,
                                           const ASN1_ITEM *it,
                                           const char *pass, int passlen,
                                           void *obj, int zbuf)
{
    ASN1_OCTET_STRING *oct = NULL;
    unsigned char *in = NULL;
    int inlen;

    if ((oct = ASN1_OCTET_STRING_new()) == NULL) {
        PKCS12err(PKCS12_F_PKCS12_ITEM_I2D_ENCRYPT, ERR_R_MALLOC_FAILURE);
        goto err;
    }
    inlen = ASN1_item_i2d(obj, &in, it);
    if (!in) {
        PKCS12err(PKCS12_F_PKCS12_ITEM_I2D_ENCRYPT, PKCS12_R_ENCODE_ERROR);
        goto err;
    }
    if (!PKCS12_pbe_crypt(algor, pass, passlen, in, inlen, &oct->data,
                          &oct->length, 1)) {
        PKCS12err(PKCS12_F_PKCS12_ITEM_I2D_ENCRYPT, PKCS12_R_ENCRYPT_ERROR);
        OPENSSL_free(in);
        goto err;
    }
    if (zbuf)
        OPENSSL_cleanse(in, inlen);
    OPENSSL_free(in);
    return oct;
 err:
    ASN1_OCTET_STRING_free(oct);
    return NULL;
}