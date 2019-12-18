#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* bytes; scalar_t__ modified; } ;
typedef  TYPE_2__ X509_NAME ;
struct TYPE_5__ {int length; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  ASN1_VALUE ;
typedef  int /*<<< orphan*/  ASN1_ITEM ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int x509_name_canon (TYPE_2__*) ; 
 int x509_name_encode (TYPE_2__*) ; 

__attribute__((used)) static int x509_name_ex_i2d(ASN1_VALUE **val, unsigned char **out,
                            const ASN1_ITEM *it, int tag, int aclass)
{
    int ret;
    X509_NAME *a = (X509_NAME *)*val;
    if (a->modified) {
        ret = x509_name_encode(a);
        if (ret < 0)
            return ret;
        ret = x509_name_canon(a);
        if (ret < 0)
            return ret;
    }
    ret = a->bytes->length;
    if (out != NULL) {
        memcpy(*out, a->bytes->data, ret);
        *out += ret;
    }
    return ret;
}