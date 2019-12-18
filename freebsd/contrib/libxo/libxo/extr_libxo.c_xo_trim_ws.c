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
struct TYPE_3__ {char* xb_curp; } ;
typedef  TYPE_1__ xo_buffer_t ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  memmove (char*,char*,int) ; 

__attribute__((used)) static ssize_t
xo_trim_ws (xo_buffer_t *xbp, ssize_t len)
{
    char *cp, *sp, *ep;
    ssize_t delta;

    /* First trim leading space */
    for (cp = sp = xbp->xb_curp, ep = cp + len; cp < ep; cp++) {
	if (*cp != ' ')
	    break;
    }

    delta = cp - sp;
    if (delta) {
	len -= delta;
	memmove(sp, cp, len);
    }

    /* Then trim off the end */
    for (cp = xbp->xb_curp, sp = ep = cp + len; cp < ep; ep--) {
	if (ep[-1] != ' ')
	    break;
    }

    delta = sp - ep;
    if (delta) {
	len -= delta;
	cp[len] = '\0';
    }

    return len;
}