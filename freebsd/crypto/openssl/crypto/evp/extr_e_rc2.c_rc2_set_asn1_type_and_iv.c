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
typedef  int /*<<< orphan*/  EVP_CIPHER_CTX ;
typedef  int /*<<< orphan*/  ASN1_TYPE ;

/* Variables and functions */
 int ASN1_TYPE_set_int_octetstring (int /*<<< orphan*/ *,long,unsigned char*,int) ; 
 int EVP_CIPHER_CTX_iv_length (int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_CIPHER_CTX_original_iv (int /*<<< orphan*/ *) ; 
 long rc2_meth_to_magic (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rc2_set_asn1_type_and_iv(EVP_CIPHER_CTX *c, ASN1_TYPE *type)
{
    long num;
    int i = 0, j;

    if (type != NULL) {
        num = rc2_meth_to_magic(c);
        j = EVP_CIPHER_CTX_iv_length(c);
        i = ASN1_TYPE_set_int_octetstring(type, num,
                                          (unsigned char *)EVP_CIPHER_CTX_original_iv(c),
                                          j);
    }
    return i;
}