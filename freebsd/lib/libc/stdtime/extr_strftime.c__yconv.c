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
typedef  int /*<<< orphan*/  locale_t ;

/* Variables and functions */
 int const DIVISOR ; 
 char* _add (char*,char*,char const* const) ; 
 char* _conv (int,char*,char*,char const* const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
_yconv(const int a, const int b, const int convert_top, const int convert_yy,
    char *pt, const char * const ptlim, locale_t  loc)
{
	register int	lead;
	register int	trail;

#define	DIVISOR	100
	trail = a % DIVISOR + b % DIVISOR;
	lead = a / DIVISOR + b / DIVISOR + trail / DIVISOR;
	trail %= DIVISOR;
	if (trail < 0 && lead > 0) {
		trail += DIVISOR;
		--lead;
	} else if (lead < 0 && trail > 0) {
		trail -= DIVISOR;
		++lead;
	}
	if (convert_top) {
		if (lead == 0 && trail < 0)
			pt = _add("-0", pt, ptlim);
		else	pt = _conv(lead, "%02d", pt, ptlim, loc);
	}
	if (convert_yy)
		pt = _conv(((trail < 0) ? -trail : trail), "%02d", pt,
		     ptlim, loc);
	return (pt);
}