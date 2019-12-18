#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  buf ;
struct TYPE_4__ {int /*<<< orphan*/  length; int /*<<< orphan*/ * data; } ;
typedef  int /*<<< orphan*/  BIO ;
typedef  TYPE_1__ ASN1_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_F_I2A_ASN1_OBJECT ; 
 int /*<<< orphan*/  ASN1err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ BIO_dump (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int BIO_write (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 char* OPENSSL_malloc (int) ; 
 int i2t_ASN1_OBJECT (char*,int,TYPE_1__ const*) ; 

int i2a_ASN1_OBJECT(BIO *bp, const ASN1_OBJECT *a)
{
    char buf[80], *p = buf;
    int i;

    if ((a == NULL) || (a->data == NULL))
        return BIO_write(bp, "NULL", 4);
    i = i2t_ASN1_OBJECT(buf, sizeof(buf), a);
    if (i > (int)(sizeof(buf) - 1)) {
        if ((p = OPENSSL_malloc(i + 1)) == NULL) {
            ASN1err(ASN1_F_I2A_ASN1_OBJECT, ERR_R_MALLOC_FAILURE);
            return -1;
        }
        i2t_ASN1_OBJECT(p, i + 1, a);
    }
    if (i <= 0) {
        i = BIO_write(bp, "<INVALID>", 9);
        i += BIO_dump(bp, (const char *)a->data, a->length);
        return i;
    }
    BIO_write(bp, p, i);
    if (p != buf)
        OPENSSL_free(p);
    return i;
}