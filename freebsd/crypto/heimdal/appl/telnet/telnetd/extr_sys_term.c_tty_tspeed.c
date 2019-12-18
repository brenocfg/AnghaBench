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
struct termspeeds {int speed; int value; } ;

/* Variables and functions */
 int /*<<< orphan*/  cfsetospeed (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  termbuf ; 
 struct termspeeds* termspeeds ; 

void
tty_tspeed(int val)
{
#ifdef	DECODE_BAUD
    struct termspeeds *tp;

    for (tp = termspeeds; (tp->speed != -1) && (val > tp->speed); tp++)
	;
    if (tp->speed == -1)	/* back up to last valid value */
	--tp;
    cfsetospeed(&termbuf, tp->value);
#else	/* DECODE_BUAD */
    cfsetospeed(&termbuf, val);
#endif	/* DECODE_BUAD */
}