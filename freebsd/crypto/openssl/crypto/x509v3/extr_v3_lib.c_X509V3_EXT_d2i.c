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
typedef  int /*<<< orphan*/  X509_EXTENSION ;
struct TYPE_3__ {void* (* d2i ) (int /*<<< orphan*/ *,unsigned char const**,int) ;scalar_t__ it; } ;
typedef  TYPE_1__ X509V3_EXT_METHOD ;
typedef  int /*<<< orphan*/  ASN1_STRING ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_ITEM_ptr (scalar_t__) ; 
 unsigned char* ASN1_STRING_get0_data (int /*<<< orphan*/ *) ; 
 int ASN1_STRING_length (int /*<<< orphan*/ *) ; 
 void* ASN1_item_d2i (int /*<<< orphan*/ *,unsigned char const**,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* X509V3_EXT_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * X509_EXTENSION_get_data (int /*<<< orphan*/ *) ; 
 void* stub1 (int /*<<< orphan*/ *,unsigned char const**,int) ; 

void *X509V3_EXT_d2i(X509_EXTENSION *ext)
{
    const X509V3_EXT_METHOD *method;
    const unsigned char *p;
    ASN1_STRING *extvalue;
    int extlen;

    if ((method = X509V3_EXT_get(ext)) == NULL)
        return NULL;
    extvalue = X509_EXTENSION_get_data(ext);
    p = ASN1_STRING_get0_data(extvalue);
    extlen = ASN1_STRING_length(extvalue);
    if (method->it)
        return ASN1_item_d2i(NULL, &p, extlen, ASN1_ITEM_ptr(method->it));
    return method->d2i(NULL, &p, extlen);
}