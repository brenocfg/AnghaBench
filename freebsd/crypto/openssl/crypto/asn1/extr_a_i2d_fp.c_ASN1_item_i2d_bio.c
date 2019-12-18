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
typedef  int /*<<< orphan*/  BIO ;
typedef  int /*<<< orphan*/  ASN1_ITEM ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_F_ASN1_ITEM_I2D_BIO ; 
 int ASN1_item_i2d (void*,unsigned char**,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ASN1err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int BIO_write (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 

int ASN1_item_i2d_bio(const ASN1_ITEM *it, BIO *out, void *x)
{
    unsigned char *b = NULL;
    int i, j = 0, n, ret = 1;

    n = ASN1_item_i2d(x, &b, it);
    if (b == NULL) {
        ASN1err(ASN1_F_ASN1_ITEM_I2D_BIO, ERR_R_MALLOC_FAILURE);
        return 0;
    }

    for (;;) {
        i = BIO_write(out, &(b[j]), n);
        if (i == n)
            break;
        if (i <= 0) {
            ret = 0;
            break;
        }
        j += i;
        n -= i;
    }
    OPENSSL_free(b);
    return ret;
}