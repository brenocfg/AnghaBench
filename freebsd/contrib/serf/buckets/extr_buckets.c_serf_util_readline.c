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
#define  SERF_NEWLINE_CR 132 
#define  SERF_NEWLINE_CRLF 131 
#define  SERF_NEWLINE_CRLF_SPLIT 130 
#define  SERF_NEWLINE_LF 129 
#define  SERF_NEWLINE_NONE 128 
 int /*<<< orphan*/  find_crlf (char const**,int*,int*) ; 
 char* memchr (char const*,char,int) ; 

void serf_util_readline(
    const char **data,
    apr_size_t *len,
    int acceptable,
    int *found)
{
    const char *start;
    const char *cr;
    const char *lf;
    int want_cr;
    int want_crlf;
    int want_lf;

    /* If _only_ CRLF is acceptable, then the scanning needs a loop to
     * skip false hits on CR characters. Use a separate function.
     */
    if (acceptable == SERF_NEWLINE_CRLF) {
        find_crlf(data, len, found);
        return;
    }

    start = *data;
    cr = lf = NULL;
    want_cr = acceptable & SERF_NEWLINE_CR;
    want_crlf = acceptable & SERF_NEWLINE_CRLF;
    want_lf = acceptable & SERF_NEWLINE_LF;

    if (want_cr || want_crlf) {
        cr = memchr(start, '\r', *len);
    }
    if (want_lf) {
        lf = memchr(start, '\n', *len);
    }

    if (cr != NULL) {
        if (lf != NULL) {
            if (cr + 1 == lf)
                *found = want_crlf ? SERF_NEWLINE_CRLF : SERF_NEWLINE_CR;
            else if (want_cr && cr < lf)
                *found = SERF_NEWLINE_CR;
            else
                *found = SERF_NEWLINE_LF;
        }
        else if (cr == start + *len - 1) {
            /* the CR occurred in the last byte of the buffer. this could be
             * a CRLF split across the data boundary.
             * ### FIX THIS LOGIC? does caller need to detect?
             */
            *found = want_crlf ? SERF_NEWLINE_CRLF_SPLIT : SERF_NEWLINE_CR;
        }
        else if (want_cr)
            *found = SERF_NEWLINE_CR;
        else /* want_crlf */
            *found = SERF_NEWLINE_NONE;
    }
    else if (lf != NULL)
        *found = SERF_NEWLINE_LF;
    else
        *found = SERF_NEWLINE_NONE;

    switch (*found) {
      case SERF_NEWLINE_LF:
        *data = lf + 1;
        break;
      case SERF_NEWLINE_CR:
      case SERF_NEWLINE_CRLF:
      case SERF_NEWLINE_CRLF_SPLIT:
        *data = cr + 1 + (*found == SERF_NEWLINE_CRLF);
        break;
      case SERF_NEWLINE_NONE:
        *data += *len;
        break;
      default:
        /* Not reachable */
        return;
    }

    *len -= *data - start;
}