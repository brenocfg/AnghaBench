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
typedef  int /*<<< orphan*/  va_list ;

/* Variables and functions */
 size_t INT_MAX ; 
 int /*<<< orphan*/  _dopr (char**,int /*<<< orphan*/ *,size_t*,size_t*,int*,char const*,int /*<<< orphan*/ ) ; 

int BIO_vsnprintf(char *buf, size_t n, const char *format, va_list args)
{
    size_t retlen;
    int truncated;

    if (!_dopr(&buf, NULL, &n, &retlen, &truncated, format, args))
        return -1;

    if (truncated)
        /*
         * In case of truncation, return -1 like traditional snprintf.
         * (Current drafts for ISO/IEC 9899 say snprintf should return the
         * number of characters that would have been written, had the buffer
         * been large enough.)
         */
        return -1;
    else
        return (retlen <= INT_MAX) ? (int)retlen : -1;
}