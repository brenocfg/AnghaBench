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
struct TYPE_3__ {int len; scalar_t__ modified; int /*<<< orphan*/ * enc; } ;
typedef  int /*<<< orphan*/  ASN1_VALUE ;
typedef  int /*<<< orphan*/  ASN1_ITEM ;
typedef  TYPE_1__ ASN1_ENCODING ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_F_ASN1_ENC_SAVE ; 
 int /*<<< orphan*/  ASN1err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * OPENSSL_malloc (int) ; 
 TYPE_1__* asn1_get_enc_ptr (int /*<<< orphan*/ **,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,unsigned char const*,int) ; 

int asn1_enc_save(ASN1_VALUE **pval, const unsigned char *in, int inlen,
                  const ASN1_ITEM *it)
{
    ASN1_ENCODING *enc;
    enc = asn1_get_enc_ptr(pval, it);
    if (!enc)
        return 1;

    OPENSSL_free(enc->enc);
    if ((enc->enc = OPENSSL_malloc(inlen)) == NULL) {
        ASN1err(ASN1_F_ASN1_ENC_SAVE, ERR_R_MALLOC_FAILURE);
        return 0;
    }
    memcpy(enc->enc, in, inlen);
    enc->len = inlen;
    enc->modified = 0;

    return 1;
}