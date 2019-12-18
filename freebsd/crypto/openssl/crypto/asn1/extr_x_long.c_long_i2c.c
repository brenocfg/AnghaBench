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
struct TYPE_3__ {long size; } ;
typedef  int /*<<< orphan*/  ASN1_VALUE ;
typedef  TYPE_1__ ASN1_ITEM ;

/* Variables and functions */
 int /*<<< orphan*/  COPY_SIZE (int /*<<< orphan*/ *,long) ; 
 int /*<<< orphan*/  memcpy (long*,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int num_bits_ulong (unsigned long) ; 

__attribute__((used)) static int long_i2c(ASN1_VALUE **pval, unsigned char *cont, int *putype,
                    const ASN1_ITEM *it)
{
    long ltmp;
    unsigned long utmp, sign;
    int clen, pad, i;

    memcpy(&ltmp, pval, COPY_SIZE(*pval, ltmp));
    if (ltmp == it->size)
        return -1;
    /*
     * Convert the long to positive: we subtract one if negative so we can
     * cleanly handle the padding if only the MSB of the leading octet is
     * set.
     */
    if (ltmp < 0) {
        sign = 0xff;
        utmp = 0 - (unsigned long)ltmp - 1;
    } else {
        sign = 0;
        utmp = ltmp;
    }
    clen = num_bits_ulong(utmp);
    /* If MSB of leading octet set we need to pad */
    if (!(clen & 0x7))
        pad = 1;
    else
        pad = 0;

    /* Convert number of bits to number of octets */
    clen = (clen + 7) >> 3;

    if (cont != NULL) {
        if (pad)
            *cont++ = (unsigned char)sign;
        for (i = clen - 1; i >= 0; i--) {
            cont[i] = (unsigned char)(utmp ^ sign);
            utmp >>= 8;
        }
    }
    return clen + pad;
}