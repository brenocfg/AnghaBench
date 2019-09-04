#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct tm {scalar_t__ tm_sec; scalar_t__ tm_min; scalar_t__ tm_hour; scalar_t__ tm_year; int /*<<< orphan*/  tm_mon; scalar_t__ tm_mday; int /*<<< orphan*/  tm_wday; } ;

/* Variables and functions */
 int H2O_TIMESTR_RFC1123_LEN ; 
 int /*<<< orphan*/  assert (int) ; 
 char* emit_digits (char*,scalar_t__,int) ; 
 char* emit_mon (char*,int /*<<< orphan*/ ) ; 
 char* emit_wday (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 

void h2o_time2str_rfc1123(char *buf, struct tm *gmt)
{
    char *p = buf;

    /* format: Fri, 19 Sep 2014 05:24:04 GMT */
    p = emit_wday(p, gmt->tm_wday);
    *p++ = ',';
    *p++ = ' ';
    p = emit_digits(p, gmt->tm_mday, 2);
    *p++ = ' ';
    p = emit_mon(p, gmt->tm_mon);
    *p++ = ' ';
    p = emit_digits(p, gmt->tm_year + 1900, 4);
    *p++ = ' ';
    p = emit_digits(p, gmt->tm_hour, 2);
    *p++ = ':';
    p = emit_digits(p, gmt->tm_min, 2);
    *p++ = ':';
    p = emit_digits(p, gmt->tm_sec, 2);
    memcpy(p, " GMT", 4);
    p += 4;
    *p = '\0';

    assert(p - buf == H2O_TIMESTR_RFC1123_LEN);
}