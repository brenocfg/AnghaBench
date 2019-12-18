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
typedef  int /*<<< orphan*/  tmp ;
struct tm {int tm_year; int tm_mon; int tm_mday; int tm_hour; int tm_min; int tm_sec; } ;
struct TYPE_3__ {scalar_t__ type; int flags; int length; scalar_t__ data; } ;
typedef  TYPE_1__ ASN1_TIME ;

/* Variables and functions */
 int ASN1_STRING_FLAG_X509_TIME ; 
 int /*<<< orphan*/  OPENSSL_gmtime_adj (struct tm*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ V_ASN1_GENERALIZEDTIME ; 
 scalar_t__ V_ASN1_UTCTIME ; 
 scalar_t__ ascii_isdigit (char) ; 
 int /*<<< orphan*/  determine_days (struct tm*) ; 
 int /*<<< orphan*/  leap_year (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct tm*,int /*<<< orphan*/ ,int) ; 

int asn1_time_to_tm(struct tm *tm, const ASN1_TIME *d)
{
    static const int min[9] = { 0, 0, 1, 1, 0, 0, 0, 0, 0 };
    static const int max[9] = { 99, 99, 12, 31, 23, 59, 59, 12, 59 };
    static const int mdays[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    char *a;
    int n, i, i2, l, o, min_l = 11, strict = 0, end = 6, btz = 5, md;
    struct tm tmp;
#if defined(CHARSET_EBCDIC)
    const char upper_z = 0x5A, num_zero = 0x30, period = 0x2E, minus = 0x2D, plus = 0x2B;
#else
    const char upper_z = 'Z', num_zero = '0', period = '.', minus = '-', plus = '+';
#endif
    /*
     * ASN1_STRING_FLAG_X509_TIME is used to enforce RFC 5280
     * time string format, in which:
     *
     * 1. "seconds" is a 'MUST'
     * 2. "Zulu" timezone is a 'MUST'
     * 3. "+|-" is not allowed to indicate a time zone
     */
    if (d->type == V_ASN1_UTCTIME) {
        if (d->flags & ASN1_STRING_FLAG_X509_TIME) {
            min_l = 13;
            strict = 1;
        }
    } else if (d->type == V_ASN1_GENERALIZEDTIME) {
        end = 7;
        btz = 6;
        if (d->flags & ASN1_STRING_FLAG_X509_TIME) {
            min_l = 15;
            strict = 1;
        } else {
            min_l = 13;
        }
    } else {
        return 0;
    }

    l = d->length;
    a = (char *)d->data;
    o = 0;
    memset(&tmp, 0, sizeof(tmp));

    /*
     * GENERALIZEDTIME is similar to UTCTIME except the year is represented
     * as YYYY. This stuff treats everything as a two digit field so make
     * first two fields 00 to 99
     */

    if (l < min_l)
        goto err;
    for (i = 0; i < end; i++) {
        if (!strict && (i == btz) && ((a[o] == upper_z) || (a[o] == plus) || (a[o] == minus))) {
            i++;
            break;
        }
        if (!ascii_isdigit(a[o]))
            goto err;
        n = a[o] - num_zero;
        /* incomplete 2-digital number */
        if (++o == l)
            goto err;

        if (!ascii_isdigit(a[o]))
            goto err;
        n = (n * 10) + a[o] - num_zero;
        /* no more bytes to read, but we haven't seen time-zone yet */
        if (++o == l)
            goto err;

        i2 = (d->type == V_ASN1_UTCTIME) ? i + 1 : i;

        if ((n < min[i2]) || (n > max[i2]))
            goto err;
        switch (i2) {
        case 0:
            /* UTC will never be here */
            tmp.tm_year = n * 100 - 1900;
            break;
        case 1:
            if (d->type == V_ASN1_UTCTIME)
                tmp.tm_year = n < 50 ? n + 100 : n;
            else
                tmp.tm_year += n;
            break;
        case 2:
            tmp.tm_mon = n - 1;
            break;
        case 3:
            /* check if tm_mday is valid in tm_mon */
            if (tmp.tm_mon == 1) {
                /* it's February */
                md = mdays[1] + leap_year(tmp.tm_year + 1900);
            } else {
                md = mdays[tmp.tm_mon];
            }
            if (n > md)
                goto err;
            tmp.tm_mday = n;
            determine_days(&tmp);
            break;
        case 4:
            tmp.tm_hour = n;
            break;
        case 5:
            tmp.tm_min = n;
            break;
        case 6:
            tmp.tm_sec = n;
            break;
        }
    }

    /*
     * Optional fractional seconds: decimal point followed by one or more
     * digits.
     */
    if (d->type == V_ASN1_GENERALIZEDTIME && a[o] == period) {
        if (strict)
            /* RFC 5280 forbids fractional seconds */
            goto err;
        if (++o == l)
            goto err;
        i = o;
        while ((o < l) && ascii_isdigit(a[o]))
            o++;
        /* Must have at least one digit after decimal point */
        if (i == o)
            goto err;
        /* no more bytes to read, but we haven't seen time-zone yet */
        if (o == l)
            goto err;
    }

    /*
     * 'o' will never point to '\0' at this point, the only chance
     * 'o' can point to '\0' is either the subsequent if or the first
     * else if is true.
     */
    if (a[o] == upper_z) {
        o++;
    } else if (!strict && ((a[o] == plus) || (a[o] == minus))) {
        int offsign = a[o] == minus ? 1 : -1;
        int offset = 0;

        o++;
        /*
         * if not equal, no need to do subsequent checks
         * since the following for-loop will add 'o' by 4
         * and the final return statement will check if 'l'
         * and 'o' are equal.
         */
        if (o + 4 != l)
            goto err;
        for (i = end; i < end + 2; i++) {
            if (!ascii_isdigit(a[o]))
                goto err;
            n = a[o] - num_zero;
            o++;
            if (!ascii_isdigit(a[o]))
                goto err;
            n = (n * 10) + a[o] - num_zero;
            i2 = (d->type == V_ASN1_UTCTIME) ? i + 1 : i;
            if ((n < min[i2]) || (n > max[i2]))
                goto err;
            /* if tm is NULL, no need to adjust */
            if (tm != NULL) {
                if (i == end)
                    offset = n * 3600;
                else if (i == end + 1)
                    offset += n * 60;
            }
            o++;
        }
        if (offset && !OPENSSL_gmtime_adj(&tmp, 0, offset * offsign))
            goto err;
    } else {
        /* not Z, or not +/- in non-strict mode */
        goto err;
    }
    if (o == l) {
        /* success, check if tm should be filled */
        if (tm != NULL)
            *tm = tmp;
        return 1;
    }
 err:
    return 0;
}