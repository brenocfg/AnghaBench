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
typedef  int /*<<< orphan*/  l_fp ;

/* Variables and functions */
 int atolfp (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ isdigit (unsigned char) ; 
 scalar_t__ isspace (unsigned char) ; 

int
mstolfp(
	const char *str,
	l_fp *lfp
	)
{
	register const char *cp;
	register char *bp;
	register const char *cpdec;
	char buf[100];

	/*
	 * We understand numbers of the form:
	 *
	 * [spaces][-][digits][.][digits][spaces|\n|\0]
	 *
	 * This is one enormous hack.  Since I didn't feel like
	 * rewriting the decoding routine for milliseconds, what
	 * is essentially done here is to make a copy of the string
	 * with the decimal moved over three places so the seconds
	 * decoding routine can be used.
	 */
	bp = buf;
	cp = str;
	while (isspace((unsigned char)*cp))
	    cp++;
	
	if (*cp == '-') {
		*bp++ = '-';
		cp++;
	}

	if (*cp != '.' && !isdigit((unsigned char)*cp))
	    return 0;


	/*
	 * Search forward for the decimal point or the end of the string.
	 */
	cpdec = cp;
	while (isdigit((unsigned char)*cpdec))
	    cpdec++;

	/*
	 * Found something.  If we have more than three digits copy the
	 * excess over, else insert a leading 0.
	 */
	if ((cpdec - cp) > 3) {
		do {
			*bp++ = (char)*cp++;
		} while ((cpdec - cp) > 3);
	} else {
		*bp++ = '0';
	}

	/*
	 * Stick the decimal in.  If we've got less than three digits in
	 * front of the millisecond decimal we insert the appropriate number
	 * of zeros.
	 */
	*bp++ = '.';
	if ((cpdec - cp) < 3) {
		size_t i = 3 - (cpdec - cp);
		do {
			*bp++ = '0';
		} while (--i > 0);
	}

	/*
	 * Copy the remainder up to the millisecond decimal.  If cpdec
	 * is pointing at a decimal point, copy in the trailing number too.
	 */
	while (cp < cpdec)
	    *bp++ = (char)*cp++;
	
	if (*cp == '.') {
		cp++;
		while (isdigit((unsigned char)*cp))
		    *bp++ = (char)*cp++;
	}
	*bp = '\0';

	/*
	 * Check to make sure the string is properly terminated.  If
	 * so, give the buffer to the decoding routine.
	 */
	if (*cp != '\0' && !isspace((unsigned char)*cp))
	    return 0;
	return atolfp(buf, lfp);
}