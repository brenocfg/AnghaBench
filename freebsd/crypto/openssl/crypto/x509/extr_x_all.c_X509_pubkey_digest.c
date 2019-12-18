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
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_3__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  EVP_MD ;
typedef  TYPE_1__ ASN1_BIT_STRING ;

/* Variables and functions */
 int EVP_Digest (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,unsigned int*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 TYPE_1__* X509_get0_pubkey_bitstr (int /*<<< orphan*/  const*) ; 

int X509_pubkey_digest(const X509 *data, const EVP_MD *type,
                       unsigned char *md, unsigned int *len)
{
    ASN1_BIT_STRING *key;
    key = X509_get0_pubkey_bitstr(data);
    if (!key)
        return 0;
    return EVP_Digest(key->data, key->length, md, len, type, NULL);
}