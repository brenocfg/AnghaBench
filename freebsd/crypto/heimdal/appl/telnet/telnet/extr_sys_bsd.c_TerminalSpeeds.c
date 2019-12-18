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
struct termspeeds {int speed; long value; } ;

/* Variables and functions */
 long cfgetispeed (int /*<<< orphan*/ *) ; 
 long cfgetospeed (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  old_tc ; 
 struct termspeeds* termspeeds ; 

void
TerminalSpeeds(long *input_speed, long *output_speed)
{
#ifdef	DECODE_BAUD
    struct termspeeds *tp;
#endif	/* DECODE_BAUD */
    long in, out;

    out = cfgetospeed(&old_tc);
    in = cfgetispeed(&old_tc);
    if (in == 0)
	in = out;

#ifdef	DECODE_BAUD
    tp = termspeeds;
    while ((tp->speed != -1) && (tp->value < in))
	tp++;
    *input_speed = tp->speed;

    tp = termspeeds;
    while ((tp->speed != -1) && (tp->value < out))
	tp++;
    *output_speed = tp->speed;
#else	/* DECODE_BAUD */
	*input_speed = in;
	*output_speed = out;
#endif	/* DECODE_BAUD */
}