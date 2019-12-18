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
typedef  scalar_t__ off_t ;

/* Variables and functions */
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*,char const*,char const*) ; 
 scalar_t__ strtoll (char const*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static off_t
argtooff(const char *arg, const char *msg)
{
    char *s;
    off_t x;

    errno = 0;
    x = strtoll(arg, &s, 0);
    /* allow at most one extra char */
    if (errno || x < 0 || (s[0] && s[1]) )
	errx(1, "%s: bad %s", arg, msg);
    if (*s) {	/* the extra char is the multiplier */
	switch (*s) {
	default:
	    errx(1, "%s: bad %s", arg, msg);
	    /* notreached */

	case 's':		/* sector */
	case 'S':
	    x <<= 9;		/* times 512 */
	    break;

	case 'k':		/* kilobyte */
	case 'K':
	    x <<= 10;		/* times 1024 */
	    break;

	case 'm':		/* megabyte */
	case 'M':
	    x <<= 20;		/* times 1024*1024 */
	    break;

	case 'g':		/* gigabyte */
	case 'G':
	    x <<= 30;		/* times 1024*1024*1024 */
	    break;

	case 'p':		/* partition start */
	case 'P':
	case 'l':		/* partition length */
	case 'L':
	    errx(1, "%s: not supported yet %s", arg, msg);
	    /* notreached */
	}
    }
    return x;
}