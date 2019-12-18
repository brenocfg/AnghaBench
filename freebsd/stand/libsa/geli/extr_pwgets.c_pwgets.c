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

/* Variables and functions */
 int getchar () ; 
 int /*<<< orphan*/  putchar (char) ; 

void
pwgets(char *buf, int n, int hide)
{
    int c;
    char *lp;

    for (lp = buf;;)
	switch (c = getchar() & 0177) {
	case '\n':
	case '\r':
	    *lp = '\0';
	    putchar('\n');
	    return;
	case '\b':
	case '\177':
	    if (lp > buf) {
		lp--;
		if (hide == 0) {
			putchar('\b');
			putchar(' ');
			putchar('\b');
		}
	    }
	    break;
	case 'u'&037:
	case 'w'&037:
	    lp = buf;
	    putchar('\n');
	    break;
	default:
	    if ((n < 1) || ((lp - buf) < n - 1)) {
		*lp++ = c;
		if (hide == 0) {
			putchar('*');
		}
	    }
	}
    /*NOTREACHED*/
}