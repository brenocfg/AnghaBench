#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct printf_info {int prec; char showsign; int spec; scalar_t__ left; int width; scalar_t__ alt; int /*<<< orphan*/  pad; scalar_t__ is_long_double; } ;
struct __printf_io {int dummy; } ;
struct TYPE_2__ {char* thousands_sep; char* grouping; char* decimal_point; } ;

/* Variables and functions */
 int BUF ; 
 char const CHAR_MAX ; 
 int DEFPREC ; 
 int INT_MAX ; 
 int /*<<< orphan*/  MAXEXPDIG ; 
 int /*<<< orphan*/  PRINTANDPAD (char*,char*,char const,int) ; 
 char* __hdtoa (double,char const*,int,int*,int*,char**) ; 
 char* __hldtoa (long double,char const*,int,int*,int*,char**) ; 
 char* __ldtoa (long double*,int,int,int*,int*,char**) ; 
 char* __lowercase_hex ; 
 int /*<<< orphan*/  __printf_flush (struct __printf_io*) ; 
 scalar_t__ __printf_pad (struct __printf_io*,int,int) ; 
 scalar_t__ __printf_puts (struct __printf_io*,char*,int) ; 
 char* __uppercase_hex ; 
 int /*<<< orphan*/  assert (int) ; 
 char* dtoa (double,int,int,int*,int*,char**) ; 
 int exponent (char*,int,char) ; 
 int /*<<< orphan*/  freedtoa (char*) ; 
 TYPE_1__* localeconv () ; 

int
__printf_render_float(struct __printf_io *io, const struct printf_info *pi, const void *const *arg)
{
	int prec;		/* precision from format; <0 for N/A */
	char *dtoaresult;	/* buffer allocated by dtoa */
	char expchar;		/* exponent character: [eEpP\0] */
	char *cp;
	int expt;		/* integer value of exponent */
	int signflag;		/* true if float is negative */
	char *dtoaend;		/* pointer to end of converted digits */
	char sign;		/* sign prefix (' ', '+', '-', or \0) */
	int size;		/* size of converted field or string */
	int ndig;		/* actual number of digits returned by dtoa */
	int expsize;		/* character count for expstr */
	char expstr[MAXEXPDIG+2];	/* buffer for exponent string: e+ZZZ */
	int nseps;		/* number of group separators with ' */
	int nrepeats;		/* number of repeats of the last group */
	const char *grouping;	/* locale specific numeric grouping rules */
	int lead;		/* sig figs before decimal or group sep */
	long double ld;
	double d;
	int realsz;		/* field size expanded by dprec, sign, etc */
	int dprec;		/* a copy of prec if [diouxX], 0 otherwise */
	char ox[2];		/* space for 0x; ox[1] is either x, X, or \0 */
	int ret;		/* return value accumulator */
	char *decimal_point;	/* locale specific decimal point */
	int n2;			/* XXX: for PRINTANDPAD */
	char thousands_sep;	/* locale specific thousands separator */
	char buf[BUF];		/* buffer with space for digits of uintmax_t */
	const char *xdigs;
	int flag;

	prec = pi->prec;
	ox[1] = '\0';
	sign = pi->showsign;
	flag = 0;
	ret = 0;

	thousands_sep = *(localeconv()->thousands_sep);
	grouping = NULL;
	if (pi->alt)
		grouping = localeconv()->grouping;
	decimal_point = localeconv()->decimal_point;
	dprec = -1;

	switch(pi->spec) {
	case 'a':
	case 'A':
		if (pi->spec == 'a') {
			ox[1] = 'x';
			xdigs = __lowercase_hex;
			expchar = 'p';
		} else {
			ox[1] = 'X';
			xdigs = __uppercase_hex;
			expchar = 'P';
		}
		if (prec >= 0)
			prec++;
		if (pi->is_long_double) {
			ld = *((long double *)arg[0]);
			dtoaresult = cp =
			    __hldtoa(ld, xdigs, prec,
			    &expt, &signflag, &dtoaend);
		} else {
			d = *((double *)arg[0]);
			dtoaresult = cp =
			    __hdtoa(d, xdigs, prec,
			    &expt, &signflag, &dtoaend);
		}
		if (prec < 0)
			prec = dtoaend - cp;
		if (expt == INT_MAX)
			ox[1] = '\0';
		goto fp_common;
	case 'e':
	case 'E':
		expchar = pi->spec;
		if (prec < 0)	/* account for digit before decpt */
			prec = DEFPREC + 1;
		else
			prec++;
		break;
	case 'f':
	case 'F':
		expchar = '\0';
		break;
	case 'g':
	case 'G':
		expchar = pi->spec - ('g' - 'e');
		if (prec == 0)
			prec = 1;
		break;
	default:
		assert(pi->spec == 'f');
	}

	if (prec < 0)
		prec = DEFPREC;
	if (pi->is_long_double) {
		ld = *((long double *)arg[0]);
		dtoaresult = cp =
		    __ldtoa(&ld, expchar ? 2 : 3, prec,
		    &expt, &signflag, &dtoaend);
	} else {
		d = *((double *)arg[0]);
		dtoaresult = cp =
		    dtoa(d, expchar ? 2 : 3, prec,
		    &expt, &signflag, &dtoaend);
		if (expt == 9999)
			expt = INT_MAX;
	}
fp_common:
	if (signflag)
		sign = '-';
	if (expt == INT_MAX) {	/* inf or nan */
		if (*cp == 'N') {
			cp = (pi->spec >= 'a') ? "nan" : "NAN";
			sign = '\0';
		} else
			cp = (pi->spec >= 'a') ? "inf" : "INF";
		size = 3;
		flag = 1;
		goto here;
	}
	ndig = dtoaend - cp;
	if (pi->spec == 'g' || pi->spec == 'G') {
		if (expt > -4 && expt <= prec) {
			/* Make %[gG] smell like %[fF] */
			expchar = '\0';
			if (pi->alt)
				prec -= expt;
			else
				prec = ndig - expt;
			if (prec < 0)
				prec = 0;
		} else {
			/*
			 * Make %[gG] smell like %[eE], but
			 * trim trailing zeroes if no # flag.
			 */
			if (!pi->alt)
				prec = ndig;
		}
	}
	if (expchar) {
		expsize = exponent(expstr, expt - 1, expchar);
		size = expsize + prec;
		if (prec > 1 || pi->alt)
			++size;
	} else {
		/* space for digits before decimal point */
		if (expt > 0)
			size = expt;
		else	/* "0" */
			size = 1;
		/* space for decimal pt and following digits */
		if (prec || pi->alt)
			size += prec + 1;
		if (grouping && expt > 0) {
			/* space for thousands' grouping */
			nseps = nrepeats = 0;
			lead = expt;
			while (*grouping != CHAR_MAX) {
				if (lead <= *grouping)
					break;
				lead -= *grouping;
				if (*(grouping+1)) {
					nseps++;
					grouping++;
				} else
					nrepeats++;
			}
			size += nseps + nrepeats;
		} else
			lead = expt;
	}

here:
	/*
	 * All reasonable formats wind up here.  At this point, `cp'
	 * points to a string which (if not flags&LADJUST) should be
	 * padded out to `width' places.  If flags&ZEROPAD, it should
	 * first be prefixed by any sign or other prefix; otherwise,
	 * it should be blank padded before the prefix is emitted.
	 * After any left-hand padding and prefixing, emit zeroes
	 * required by a decimal [diouxX] precision, then print the
	 * string proper, then emit zeroes required by any leftover
	 * floating precision; finally, if LADJUST, pad with blanks.
	 *
	 * Compute actual size, so we know how much to pad.
	 * size excludes decimal prec; realsz includes it.
	 */
	realsz = dprec > size ? dprec : size;
	if (sign)
		realsz++;
	if (ox[1])
		realsz += 2;

	/* right-adjusting blank padding */
	if (pi->pad != '0' && pi->left == 0)
		ret += __printf_pad(io, pi->width - realsz, 0);

	/* prefix */
	if (sign)
		ret += __printf_puts(io, &sign, 1);

	if (ox[1]) {	/* ox[1] is either x, X, or \0 */
		ox[0] = '0';
		ret += __printf_puts(io, ox, 2);
	}

	/* right-adjusting zero padding */
	if (pi->pad == '0' && pi->left == 0)
		ret += __printf_pad(io, pi->width - realsz, 1);

	/* leading zeroes from decimal precision */
	ret += __printf_pad(io, dprec - size, 1);

	if (flag)
		ret += __printf_puts(io, cp, size);
	else {
		/* glue together f_p fragments */
		if (!expchar) {	/* %[fF] or sufficiently short %[gG] */
			if (expt <= 0) {
				ret += __printf_puts(io, "0", 1);
				if (prec || pi->alt)
					ret += __printf_puts(io, decimal_point, 1);
				ret += __printf_pad(io, -expt, 1);
				/* already handled initial 0's */
				prec += expt;
			} else {
				PRINTANDPAD(cp, dtoaend, lead, 1);
				cp += lead;
				if (grouping) {
					while (nseps>0 || nrepeats>0) {
						if (nrepeats > 0)
							nrepeats--;
						else {
							grouping--;
							nseps--;
						}
						ret += __printf_puts(io, &thousands_sep, 1);
						PRINTANDPAD(cp,dtoaend,
						    *grouping, 1);
						cp += *grouping;
					}
					if (cp > dtoaend)
						cp = dtoaend;
				}
				if (prec || pi->alt)
					ret += __printf_puts(io, decimal_point,1);
			}
			PRINTANDPAD(cp, dtoaend, prec, 1);
		} else {	/* %[eE] or sufficiently long %[gG] */
			if (prec > 1 || pi->alt) {
				buf[0] = *cp++;
				buf[1] = *decimal_point;
				ret += __printf_puts(io, buf, 2);
				ret += __printf_puts(io, cp, ndig-1);
				ret += __printf_pad(io, prec - ndig, 1);
			} else	/* XeYYY */
				ret += __printf_puts(io, cp, 1);
			ret += __printf_puts(io, expstr, expsize);
		}
	}
	/* left-adjusting padding (always blank) */
	if (pi->left)
		ret += __printf_pad(io, pi->width - realsz, 0);

	__printf_flush(io);
	if (dtoaresult != NULL)
		freedtoa(dtoaresult);

	return (ret);
}