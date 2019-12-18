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
c_prev_word(Char *p, Char *low, int n)
{
    p--;

    if (!VImode) {
	while (n--) {
	    while ((p >= low) && !isword(*p)) 
		p--;
	    while ((p >= low) && isword(*p)) 
		p--;
	}
      
	/* cp now points to one character before the word */
	p++;
	if (p < low)
	    p = low;
	/* cp now points where we want it */
	return(p);
    }
  
    while (n--) {
        int  c_class;

        if (p < low)
            break;

        /* scan until beginning of current word (may be all whitespace!) */
        c_class = c_to_class(*p);
        while ((p >= low) && c_class == c_to_class(*p))
            p--;

        /* if this was a non_whitespace word, we're ready */
        if (c_class != C_CLASS_WHITE)
            continue;

        /* otherwise, move back to beginning of the word just found */
        c_class = c_to_class(*p);
        while ((p >= low) && c_class == c_to_class(*p))
            p--;
    }

    p++;                        /* correct overshoot */

    return (p);
}