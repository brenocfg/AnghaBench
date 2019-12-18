#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
struct TYPE_5__ {int* _p; scalar_t__ _r; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 int HAVESIGN ; 
 int NDIGITS ; 
 int NZDIGITS ; 
 int PFXOK ; 
 int SIGNOK ; 
 scalar_t__ __srefill (TYPE_1__*) ; 
 int /*<<< orphan*/  __ungetc (int,TYPE_1__*) ; 

__attribute__((used)) static __inline int
parseint(FILE *fp, char * __restrict buf, int width, int base, int flags)
{
	/* `basefix' is used to avoid `if' tests */
	static const short basefix[17] =
		{ 10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
	char *p;
	int c;

	flags |= SIGNOK | NDIGITS | NZDIGITS;
	for (p = buf; width; width--) {
		c = *fp->_p;
		/*
		 * Switch on the character; `goto ok' if we accept it
		 * as a part of number.
		 */
		switch (c) {

		/*
		 * The digit 0 is always legal, but is special.  For
		 * %i conversions, if no digits (zero or nonzero) have
		 * been scanned (only signs), we will have base==0.
		 * In that case, we should set it to 8 and enable 0x
		 * prefixing.  Also, if we have not scanned zero
		 * digits before this, do not turn off prefixing
		 * (someone else will turn it off if we have scanned
		 * any nonzero digits).
		 */
		case '0':
			if (base == 0) {
				base = 8;
				flags |= PFXOK;
			}
			if (flags & NZDIGITS)
				flags &= ~(SIGNOK|NZDIGITS|NDIGITS);
			else
				flags &= ~(SIGNOK|PFXOK|NDIGITS);
			goto ok;

		/* 1 through 7 always legal */
		case '1': case '2': case '3':
		case '4': case '5': case '6': case '7':
			base = basefix[base];
			flags &= ~(SIGNOK | PFXOK | NDIGITS);
			goto ok;

		/* digits 8 and 9 ok iff decimal or hex */
		case '8': case '9':
			base = basefix[base];
			if (base <= 8)
				break;	/* not legal here */
			flags &= ~(SIGNOK | PFXOK | NDIGITS);
			goto ok;

		/* letters ok iff hex */
		case 'A': case 'B': case 'C':
		case 'D': case 'E': case 'F':
		case 'a': case 'b': case 'c':
		case 'd': case 'e': case 'f':
			/* no need to fix base here */
			if (base <= 10)
				break;	/* not legal here */
			flags &= ~(SIGNOK | PFXOK | NDIGITS);
			goto ok;

		/* sign ok only as first character */
		case '+': case '-':
			if (flags & SIGNOK) {
				flags &= ~SIGNOK;
				flags |= HAVESIGN;
				goto ok;
			}
			break;

		/*
		 * x ok iff flag still set & 2nd char (or 3rd char if
		 * we have a sign).
		 */
		case 'x': case 'X':
			if (flags & PFXOK && p ==
			    buf + 1 + !!(flags & HAVESIGN)) {
				base = 16;	/* if %i */
				flags &= ~PFXOK;
				goto ok;
			}
			break;
		}

		/*
		 * If we got here, c is not a legal character for a
		 * number.  Stop accumulating digits.
		 */
		break;
	ok:
		/*
		 * c is legal: store it and look at the next.
		 */
		*p++ = c;
		if (--fp->_r > 0)
			fp->_p++;
		else if (__srefill(fp))
			break;		/* EOF */
	}
	/*
	 * If we had only a sign, it is no good; push back the sign.
	 * If the number ends in `x', it was [sign] '0' 'x', so push
	 * back the x and treat it as [sign] '0'.
	 */
	if (flags & NDIGITS) {
		if (p > buf)
			(void) __ungetc(*(u_char *)--p, fp);
		return (0);
	}
	c = ((u_char *)p)[-1];
	if (c == 'x' || c == 'X') {
		--p;
		(void) __ungetc(c, fp);
	}
	return (p - buf);
}