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
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  ND_TTEST (char const) ; 

__attribute__((used)) static const char *
parse_field(netdissect_options *ndo, const char **pptr, int *len, int *truncated)
{
    const char *s;

    /* Start of string */
    s = *pptr;
    /* Scan for the NUL terminator */
    for (;;) {
	if (*len == 0) {
	    /* Ran out of packet data without finding it */
	    return NULL;
	}
	if (!ND_TTEST(**pptr)) {
	    /* Ran out of captured data without finding it */
	    *truncated = 1;
	    return NULL;
	}
	if (**pptr == '\0') {
	    /* Found it */
	    break;
	}
	/* Keep scanning */
	(*pptr)++;
	(*len)--;
    }
    /* Skip the NUL terminator */
    (*pptr)++;
    (*len)--;
    return s;
}