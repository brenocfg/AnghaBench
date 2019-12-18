#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct tm {int tm_year; int /*<<< orphan*/  tm_sec; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_hour; int /*<<< orphan*/  tm_mday; scalar_t__ tm_mon; } ;
struct TYPE_7__ {int type; void* length; scalar_t__ data; } ;
typedef  TYPE_1__ ASN1_TIME ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_STRING_free (TYPE_1__*) ; 
 TYPE_1__* ASN1_STRING_new () ; 
 int /*<<< orphan*/  ASN1_STRING_set (TYPE_1__*,int /*<<< orphan*/ *,size_t const) ; 
 void* BIO_snprintf (char*,size_t const,char*,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int V_ASN1_GENERALIZEDTIME ; 
 int V_ASN1_UNDEF ; 
 int V_ASN1_UTCTIME ; 
 int /*<<< orphan*/  ebcdic2ascii (scalar_t__,scalar_t__,void*) ; 
 scalar_t__ is_utc (int) ; 

ASN1_TIME *asn1_time_from_tm(ASN1_TIME *s, struct tm *ts, int type)
{
    char* p;
    ASN1_TIME *tmps = NULL;
    const size_t len = 20;

    if (type == V_ASN1_UNDEF) {
        if (is_utc(ts->tm_year))
            type = V_ASN1_UTCTIME;
        else
            type = V_ASN1_GENERALIZEDTIME;
    } else if (type == V_ASN1_UTCTIME) {
        if (!is_utc(ts->tm_year))
            goto err;
    } else if (type != V_ASN1_GENERALIZEDTIME) {
        goto err;
    }

    if (s == NULL)
        tmps = ASN1_STRING_new();
    else
        tmps = s;
    if (tmps == NULL)
        return NULL;

    if (!ASN1_STRING_set(tmps, NULL, len))
        goto err;

    tmps->type = type;
    p = (char*)tmps->data;

    if (type == V_ASN1_GENERALIZEDTIME)
        tmps->length = BIO_snprintf(p, len, "%04d%02d%02d%02d%02d%02dZ",
                                    ts->tm_year + 1900, ts->tm_mon + 1,
                                    ts->tm_mday, ts->tm_hour, ts->tm_min,
                                    ts->tm_sec);
    else
        tmps->length = BIO_snprintf(p, len, "%02d%02d%02d%02d%02d%02dZ",
                                    ts->tm_year % 100, ts->tm_mon + 1,
                                    ts->tm_mday, ts->tm_hour, ts->tm_min,
                                    ts->tm_sec);

#ifdef CHARSET_EBCDIC
    ebcdic2ascii(tmps->data, tmps->data, tmps->length);
#endif
    return tmps;
 err:
    if (tmps != s)
        ASN1_STRING_free(tmps);
    return NULL;
}