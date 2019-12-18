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
typedef  int /*<<< orphan*/  ASN1_ITEM ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_F_ASN1_ITEM_DUP ; 
 void* ASN1_item_d2i (int /*<<< orphan*/ *,unsigned char const**,long,int /*<<< orphan*/  const*) ; 
 long ASN1_item_i2d (void*,unsigned char**,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ASN1err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 

void *ASN1_item_dup(const ASN1_ITEM *it, void *x)
{
    unsigned char *b = NULL;
    const unsigned char *p;
    long i;
    void *ret;

    if (x == NULL)
        return NULL;

    i = ASN1_item_i2d(x, &b, it);
    if (b == NULL) {
        ASN1err(ASN1_F_ASN1_ITEM_DUP, ERR_R_MALLOC_FAILURE);
        return NULL;
    }
    p = b;
    ret = ASN1_item_d2i(NULL, &p, i, it);
    OPENSSL_free(b);
    return ret;
}