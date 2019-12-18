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
struct tm {size_t tm_mon; int tm_year; int /*<<< orphan*/  tm_sec; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_hour; int /*<<< orphan*/  tm_mday; } ;
struct TYPE_4__ {int length; scalar_t__ type; scalar_t__ data; } ;
typedef  int /*<<< orphan*/  BIO ;
typedef  TYPE_1__ ASN1_TIME ;

/* Variables and functions */
 scalar_t__ BIO_printf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,...) ; 
 int /*<<< orphan*/  BIO_write (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ V_ASN1_GENERALIZEDTIME ; 
 int /*<<< orphan*/ * _asn1_mon ; 
 scalar_t__ ascii_isdigit (char) ; 
 int /*<<< orphan*/  asn1_time_to_tm (struct tm*,TYPE_1__ const*) ; 

int ASN1_TIME_print(BIO *bp, const ASN1_TIME *tm)
{
    char *v;
    int gmt = 0, l;
    struct tm stm;
    const char upper_z = 0x5A, period = 0x2E;

    if (!asn1_time_to_tm(&stm, tm)) {
        /* asn1_time_to_tm will check the time type */
        goto err;
    }

    l = tm->length;
    v = (char *)tm->data;
    if (v[l - 1] == upper_z)
        gmt = 1;

    if (tm->type == V_ASN1_GENERALIZEDTIME) {
        char *f = NULL;
        int f_len = 0;

        /*
         * Try to parse fractional seconds. '14' is the place of
         * 'fraction point' in a GeneralizedTime string.
         */
        if (tm->length > 15 && v[14] == period) {
            f = &v[14];
            f_len = 1;
            while (14 + f_len < l && ascii_isdigit(f[f_len]))
                ++f_len;
        }

        return BIO_printf(bp, "%s %2d %02d:%02d:%02d%.*s %d%s",
                          _asn1_mon[stm.tm_mon], stm.tm_mday, stm.tm_hour,
                          stm.tm_min, stm.tm_sec, f_len, f, stm.tm_year + 1900,
                          (gmt ? " GMT" : "")) > 0;
    } else {
        return BIO_printf(bp, "%s %2d %02d:%02d:%02d %d%s",
                          _asn1_mon[stm.tm_mon], stm.tm_mday, stm.tm_hour,
                          stm.tm_min, stm.tm_sec, stm.tm_year + 1900,
                          (gmt ? " GMT" : "")) > 0;
    }
 err:
    BIO_write(bp, "Bad time value", 14);
    return 0;
}