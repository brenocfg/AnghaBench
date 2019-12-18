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
 int /*<<< orphan*/  ASN1_F_LONG_C2I ; 
 int /*<<< orphan*/  ASN1_R_ILLEGAL_PADDING ; 
 int /*<<< orphan*/  ASN1_R_INTEGER_TOO_LARGE_FOR_LONG ; 
 int /*<<< orphan*/  ASN1err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COPY_SIZE (int /*<<< orphan*/ *,long) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ **,long*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int long_c2i(ASN1_VALUE **pval, const unsigned char *cont, int len,
                    int utype, char *free_cont, const ASN1_ITEM *it)
{
    int i;
    long ltmp;
    unsigned long utmp = 0, sign = 0x100;

    if (len > 1) {
        /*
         * Check possible pad byte.  Worst case, we're skipping past actual
         * content, but since that's only with 0x00 and 0xff and we set neg
         * accordingly, the result will be correct in the end anyway.
         */
        switch (cont[0]) {
        case 0xff:
            cont++;
            len--;
            sign = 0xff;
            break;
        case 0:
            cont++;
            len--;
            sign = 0;
            break;
        }
    }
    if (len > (int)sizeof(long)) {
        ASN1err(ASN1_F_LONG_C2I, ASN1_R_INTEGER_TOO_LARGE_FOR_LONG);
        return 0;
    }

    if (sign == 0x100) {
        /* Is it negative? */
        if (len && (cont[0] & 0x80))
            sign = 0xff;
        else
            sign = 0;
    } else if (((sign ^ cont[0]) & 0x80) == 0) { /* same sign bit? */
        ASN1err(ASN1_F_LONG_C2I, ASN1_R_ILLEGAL_PADDING);
        return 0;
    }
    utmp = 0;
    for (i = 0; i < len; i++) {
        utmp <<= 8;
        utmp |= cont[i] ^ sign;
    }
    ltmp = (long)utmp;
    if (ltmp < 0) {
        ASN1err(ASN1_F_LONG_C2I, ASN1_R_INTEGER_TOO_LARGE_FOR_LONG);
        return 0;
    }
    if (sign)
        ltmp = -ltmp - 1;
    if (ltmp == it->size) {
        ASN1err(ASN1_F_LONG_C2I, ASN1_R_INTEGER_TOO_LARGE_FOR_LONG);
        return 0;
    }
    memcpy(pval, &ltmp, COPY_SIZE(*pval, ltmp));
    return 1;
}