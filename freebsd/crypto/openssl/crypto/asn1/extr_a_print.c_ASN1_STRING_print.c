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
struct TYPE_3__ {int length; scalar_t__ data; } ;
typedef  int /*<<< orphan*/  BIO ;
typedef  TYPE_1__ ASN1_STRING ;

/* Variables and functions */
 scalar_t__ BIO_write (int /*<<< orphan*/ *,char*,int) ; 

int ASN1_STRING_print(BIO *bp, const ASN1_STRING *v)
{
    int i, n;
    char buf[80];
    const char *p;

    if (v == NULL)
        return 0;
    n = 0;
    p = (const char *)v->data;
    for (i = 0; i < v->length; i++) {
        if ((p[i] > '~') || ((p[i] < ' ') &&
                             (p[i] != '\n') && (p[i] != '\r')))
            buf[n] = '.';
        else
            buf[n] = p[i];
        n++;
        if (n >= 80) {
            if (BIO_write(bp, buf, n) <= 0)
                return 0;
            n = 0;
        }
    }
    if (n > 0)
        if (BIO_write(bp, buf, n) <= 0)
            return 0;
    return 1;
}