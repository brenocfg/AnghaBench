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
typedef  int /*<<< orphan*/  X509_ALGOR ;
struct TYPE_3__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_1__ ASN1_OCTET_STRING ;
typedef  int /*<<< orphan*/  ASN1_ITEM ;

/* Variables and functions */
 void* ASN1_item_d2i (int /*<<< orphan*/ *,unsigned char const**,int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  OPENSSL_cleanse (unsigned char*,int) ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 int /*<<< orphan*/  PKCS12_F_PKCS12_ITEM_DECRYPT_D2I ; 
 int /*<<< orphan*/  PKCS12_R_DECODE_ERROR ; 
 int /*<<< orphan*/  PKCS12_R_PKCS12_PBE_CRYPT_ERROR ; 
 int /*<<< orphan*/  PKCS12_pbe_crypt (int /*<<< orphan*/  const*,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char**,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PKCS12err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fwrite (unsigned char const*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ) ; 

void *PKCS12_item_decrypt_d2i(const X509_ALGOR *algor, const ASN1_ITEM *it,
                              const char *pass, int passlen,
                              const ASN1_OCTET_STRING *oct, int zbuf)
{
    unsigned char *out;
    const unsigned char *p;
    void *ret;
    int outlen;

    if (!PKCS12_pbe_crypt(algor, pass, passlen, oct->data, oct->length,
                          &out, &outlen, 0)) {
        PKCS12err(PKCS12_F_PKCS12_ITEM_DECRYPT_D2I,
                  PKCS12_R_PKCS12_PBE_CRYPT_ERROR);
        return NULL;
    }
    p = out;
#ifdef OPENSSL_DEBUG_DECRYPT
    {
        FILE *op;

        char fname[30];
        static int fnm = 1;
        sprintf(fname, "DER%d", fnm++);
        op = fopen(fname, "wb");
        fwrite(p, 1, outlen, op);
        fclose(op);
    }
#endif
    ret = ASN1_item_d2i(NULL, &p, outlen, it);
    if (zbuf)
        OPENSSL_cleanse(out, outlen);
    if (!ret)
        PKCS12err(PKCS12_F_PKCS12_ITEM_DECRYPT_D2I, PKCS12_R_DECODE_ERROR);
    OPENSSL_free(out);
    return ret;
}