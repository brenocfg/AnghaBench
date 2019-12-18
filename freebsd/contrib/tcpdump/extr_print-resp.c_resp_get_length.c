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
typedef  char u_char ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int INT_MAX ; 
 int /*<<< orphan*/  ND_TCHECK (char const) ; 

__attribute__((used)) static int
resp_get_length(netdissect_options *ndo, register const u_char *bp, int len, const u_char **endp)
{
    int result;
    u_char c;
    int saw_digit;
    int neg;
    int too_large;

    if (len == 0)
        goto trunc;
    ND_TCHECK(*bp);
    too_large = 0;
    neg = 0;
    if (*bp == '-') {
        neg = 1;
        bp++;
        len--;
    }
    result = 0;
    saw_digit = 0;

    for (;;) {
        if (len == 0)
            goto trunc;
        ND_TCHECK(*bp);
        c = *bp;
        if (!(c >= '0' && c <= '9')) {
            if (!saw_digit) {
                bp++;
                goto invalid;
            }
            break;
        }
        c -= '0';
        if (result > (INT_MAX / 10)) {
            /* This will overflow an int when we multiply it by 10. */
            too_large = 1;
        } else {
            result *= 10;
            if (result == ((INT_MAX / 10) * 10) && c > (INT_MAX % 10)) {
                /* This will overflow an int when we add c */
                too_large = 1;
            } else
                result += c;
        }
        bp++;
        len--;
        saw_digit = 1;
    }

    /*
     * OK, we found a non-digit character.  It should be a \r, followed
     * by a \n.
     */
    if (*bp != '\r') {
        bp++;
        goto invalid;
    }
    bp++;
    len--;
    if (len == 0)
        goto trunc;
    ND_TCHECK(*bp);
    if (*bp != '\n') {
        bp++;
        goto invalid;
    }
    bp++;
    len--;
    *endp = bp;
    if (neg) {
        /* -1 means "null", anything else is invalid */
        if (too_large || result != 1)
            return (-4);
        result = -1;
    }
    return (too_large ? -3 : result);

trunc:
    *endp = bp;
    return (-2);

invalid:
    *endp = bp;
    return (-5);
}