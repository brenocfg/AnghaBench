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
typedef  int apr_size_t ;

/* Variables and functions */
 int SERF_NEWLINE_CRLF ; 
 int SERF_NEWLINE_CRLF_SPLIT ; 
 int SERF_NEWLINE_NONE ; 
 char* memchr (char const*,char,int) ; 

__attribute__((used)) static void find_crlf(const char **data, apr_size_t *len, int *found)
{
    const char *start = *data;
    const char *end = start + *len;

    while (start < end) {
        const char *cr = memchr(start, '\r', *len);

        if (cr == NULL) {
            break;
        }
        ++cr;

        if (cr < end && cr[0] == '\n') {
            *len -= cr + 1 - start;
            *data = cr + 1;
            *found = SERF_NEWLINE_CRLF;
            return;
        }
        if (cr == end) {
            *len = 0;
            *data = end;
            *found = SERF_NEWLINE_CRLF_SPLIT;
            return;
        }

        /* It was a bare CR without an LF. Just move past it. */
        *len -= cr - start;
        start = cr;
    }

    *data = start + *len;
    *len -= *data - start;
    *found = SERF_NEWLINE_NONE;
}