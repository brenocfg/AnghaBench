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
typedef  double uintmax_t ;
typedef  double intmax_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  PF (char*,...) ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  digits ; 
 char* end_fmt ; 
 int escape (char*,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char** gargv ; 
 char getchr () ; 
 int /*<<< orphan*/  getfloating (long double*,int) ; 
 scalar_t__ getint (int*) ; 
 int /*<<< orphan*/  getnum (double*,double*,int) ; 
 char* getstr () ; 
 scalar_t__ isdigit (char) ; 
 char** maxargv ; 
 char* mknum (char*,char) ; 
 int myargc ; 
 char** myargv ; 
 int /*<<< orphan*/ * strchr (char const*,char) ; 
 char* strdup (char*) ; 
 char strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int strspn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

__attribute__((used)) static char *
printf_doformat(char *fmt, int *rval)
{
	static const char skip1[] = "#'-+ 0";
	int fieldwidth, haveprec, havewidth, mod_ldbl, precision;
	char convch, nextch;
	char start[strlen(fmt) + 1];
	char **fargv;
	char *dptr;
	int l;

	dptr = start;
	*dptr++ = '%';
	*dptr = 0;

	fmt++;

	/* look for "n$" field index specifier */
	l = strspn(fmt, digits);
	if ((l > 0) && (fmt[l] == '$')) {
		int idx = atoi(fmt);
		if (idx <= myargc) {
			gargv = &myargv[idx - 1];
		} else {
			gargv = &myargv[myargc];
		}
		if (gargv > maxargv)
			maxargv = gargv;
		fmt += l + 1;

		/* save format argument */
		fargv = gargv;
	} else {
		fargv = NULL;
	}

	/* skip to field width */
	while (*fmt && strchr(skip1, *fmt) != NULL) {
		*dptr++ = *fmt++;
		*dptr = 0;
	}

	if (*fmt == '*') {

		fmt++;
		l = strspn(fmt, digits);
		if ((l > 0) && (fmt[l] == '$')) {
			int idx = atoi(fmt);
			if (fargv == NULL) {
				warnx("incomplete use of n$");
				return (NULL);
			}
			if (idx <= myargc) {
				gargv = &myargv[idx - 1];
			} else {
				gargv = &myargv[myargc];
			}
			fmt += l + 1;
		} else if (fargv != NULL) {
			warnx("incomplete use of n$");
			return (NULL);
		}

		if (getint(&fieldwidth))
			return (NULL);
		if (gargv > maxargv)
			maxargv = gargv;
		havewidth = 1;

		*dptr++ = '*';
		*dptr = 0;
	} else {
		havewidth = 0;

		/* skip to possible '.', get following precision */
		while (isdigit(*fmt)) {
			*dptr++ = *fmt++;
			*dptr = 0;
		}
	}

	if (*fmt == '.') {
		/* precision present? */
		fmt++;
		*dptr++ = '.';

		if (*fmt == '*') {

			fmt++;
			l = strspn(fmt, digits);
			if ((l > 0) && (fmt[l] == '$')) {
				int idx = atoi(fmt);
				if (fargv == NULL) {
					warnx("incomplete use of n$");
					return (NULL);
				}
				if (idx <= myargc) {
					gargv = &myargv[idx - 1];
				} else {
					gargv = &myargv[myargc];
				}
				fmt += l + 1;
			} else if (fargv != NULL) {
				warnx("incomplete use of n$");
				return (NULL);
			}

			if (getint(&precision))
				return (NULL);
			if (gargv > maxargv)
				maxargv = gargv;
			haveprec = 1;
			*dptr++ = '*';
			*dptr = 0;
		} else {
			haveprec = 0;

			/* skip to conversion char */
			while (isdigit(*fmt)) {
				*dptr++ = *fmt++;
				*dptr = 0;
			}
		}
	} else
		haveprec = 0;
	if (!*fmt) {
		warnx("missing format character");
		return (NULL);
	}
	*dptr++ = *fmt;
	*dptr = 0;

	/*
	 * Look for a length modifier.  POSIX doesn't have these, so
	 * we only support them for floating-point conversions, which
	 * are extensions.  This is useful because the L modifier can
	 * be used to gain extra range and precision, while omitting
	 * it is more likely to produce consistent results on different
	 * architectures.  This is not so important for integers
	 * because overflow is the only bad thing that can happen to
	 * them, but consider the command  printf %a 1.1
	 */
	if (*fmt == 'L') {
		mod_ldbl = 1;
		fmt++;
		if (!strchr("aAeEfFgG", *fmt)) {
			warnx("bad modifier L for %%%c", *fmt);
			return (NULL);
		}
	} else {
		mod_ldbl = 0;
	}

	/* save the current arg offset, and set to the format arg */
	if (fargv != NULL) {
		gargv = fargv;
	}

	convch = *fmt;
	nextch = *++fmt;

	*fmt = '\0';
	switch (convch) {
	case 'b': {
		size_t len;
		char *p;
		int getout;

		/* Convert "b" to "s" for output. */
		start[strlen(start) - 1] = 's';
		if ((p = strdup(getstr())) == NULL) {
			warnx("%s", strerror(ENOMEM));
			return (NULL);
		}
		getout = escape(p, 0, &len);
		PF(start, p);
		/* Restore format for next loop. */

		free(p);
		if (getout)
			return (end_fmt);
		break;
	}
	case 'c': {
		char p;

		p = getchr();
		if (p != '\0')
			PF(start, p);
		break;
	}
	case 's': {
		const char *p;

		p = getstr();
		PF(start, p);
		break;
	}
	case 'd': case 'i': case 'o': case 'u': case 'x': case 'X': {
		char *f;
		intmax_t val;
		uintmax_t uval;
		int signedconv;

		signedconv = (convch == 'd' || convch == 'i');
		if ((f = mknum(start, convch)) == NULL)
			return (NULL);
		if (getnum(&val, &uval, signedconv))
			*rval = 1;
		if (signedconv)
			PF(f, val);
		else
			PF(f, uval);
		break;
	}
	case 'e': case 'E':
	case 'f': case 'F':
	case 'g': case 'G':
	case 'a': case 'A': {
		long double p;

		if (getfloating(&p, mod_ldbl))
			*rval = 1;
		if (mod_ldbl)
			PF(start, p);
		else
			PF(start, (double)p);
		break;
	}
	default:
		warnx("illegal format character %c", convch);
		return (NULL);
	}
	*fmt = nextch;
	/* return the gargv to the next element */
	return (fmt);
}