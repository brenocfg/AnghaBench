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
typedef  double u_char ;
typedef  scalar_t__ time_t ;

/* Variables and functions */
 double EXTRACT_LE_32BITS (double const*) ; 

__attribute__((used)) static time_t
interpret_long_date(const u_char *p)
{
    double d;
    time_t ret;

    /* this gives us seconds since jan 1st 1601 (approx) */
    d = (EXTRACT_LE_32BITS(p + 4) * 256.0 + p[3]) * (1.0e-7 * (1 << 24));

    /* now adjust by 369 years to make the secs since 1970 */
    d -= 369.0 * 365.25 * 24 * 60 * 60;

    /* and a fudge factor as we got it wrong by a few days */
    d += (3 * 24 * 60 * 60 + 6 * 60 * 60 + 2);

    if (d < 0)
	return(0);

    ret = (time_t)d;

    return(ret);
}