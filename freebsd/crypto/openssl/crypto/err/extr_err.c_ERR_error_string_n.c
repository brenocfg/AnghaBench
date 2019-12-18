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
typedef  int /*<<< orphan*/  rsbuf ;
typedef  int /*<<< orphan*/  lsbuf ;
typedef  int /*<<< orphan*/  fsbuf ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_snprintf (char*,size_t,char*,unsigned long,...) ; 
 unsigned long ERR_GET_FUNC (unsigned long) ; 
 unsigned long ERR_GET_LIB (unsigned long) ; 
 unsigned long ERR_GET_REASON (unsigned long) ; 
 char* ERR_func_error_string (unsigned long) ; 
 char* ERR_lib_error_string (unsigned long) ; 
 char* ERR_reason_error_string (unsigned long) ; 
 size_t strlen (char*) ; 

void ERR_error_string_n(unsigned long e, char *buf, size_t len)
{
    char lsbuf[64], fsbuf[64], rsbuf[64];
    const char *ls, *fs, *rs;
    unsigned long l, f, r;

    if (len == 0)
        return;

    l = ERR_GET_LIB(e);
    ls = ERR_lib_error_string(e);
    if (ls == NULL) {
        BIO_snprintf(lsbuf, sizeof(lsbuf), "lib(%lu)", l);
        ls = lsbuf;
    }

    fs = ERR_func_error_string(e);
    f = ERR_GET_FUNC(e);
    if (fs == NULL) {
        BIO_snprintf(fsbuf, sizeof(fsbuf), "func(%lu)", f);
        fs = fsbuf;
    }

    rs = ERR_reason_error_string(e);
    r = ERR_GET_REASON(e);
    if (rs == NULL) {
        BIO_snprintf(rsbuf, sizeof(rsbuf), "reason(%lu)", r);
        rs = rsbuf;
    }

    BIO_snprintf(buf, len, "error:%08lX:%s:%s:%s", e, ls, fs, rs);
    if (strlen(buf) == len - 1) {
        /* Didn't fit; use a minimal format. */
        BIO_snprintf(buf, len, "err:%lx:%lx:%lx:%lx", e, l, f, r);
    }
}