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
struct TYPE_3__ {char* xb_bufp; } ;
typedef  TYPE_1__ xo_buffer_t ;
typedef  int ssize_t ;

/* Variables and functions */
 scalar_t__ isdigit (int) ; 

__attribute__((used)) static int
xo_buf_find_last_number (xo_buffer_t *xbp, ssize_t start_offset)
{
    int rc = 0;			/* Fail with zero */
    int digit = 1;
    char *sp = xbp->xb_bufp;
    char *cp = sp + start_offset;

    while (--cp >= sp)
	if (isdigit((int) *cp))
	    break;

    for ( ; cp >= sp; cp--) {
	if (!isdigit((int) *cp))
	    break;
	rc += (*cp - '0') * digit;
	digit *= 10;
    }

    return rc;
}