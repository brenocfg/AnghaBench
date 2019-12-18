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
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 int C_CLASS_WHITE ; 
 int /*<<< orphan*/  VImode ; 
 int c_to_class (int /*<<< orphan*/ ) ; 
 scalar_t__ isword (int /*<<< orphan*/ ) ; 

__attribute__((used)) static Char *
c_next_word(Char *p, Char *high, int n)
{
    if (!VImode) {
	while (n--) {
	    while ((p < high) && !isword(*p)) 
		p++;
	    while ((p < high) && isword(*p)) 
		p++;
	}
	if (p > high)
	    p = high;
	/* p now points where we want it */
	return(p);
    }

    while (n--) {
        int  c_class;

        if (p >= high)
            break;

        /* scan until end of current word (may be all whitespace!) */
        c_class = c_to_class(*p);
        while ((p < high) && c_class == c_to_class(*p))
            p++;

        /* if this was all whitespace, we're ready */
        if (c_class == C_CLASS_WHITE)
            continue;

	/* if we've found white-space at the end of the word, skip it */
        while ((p < high) && c_to_class(*p) == C_CLASS_WHITE)
            p++;
    }

    p--;                        /* correct overshoot */

    return (p);
}