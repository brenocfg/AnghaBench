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
union arg {char intmaxarg; char uintmaxarg; char ulongarg; char uintarg; scalar_t__ intarg; scalar_t__ longarg; } ;
typedef  char uintmax_t ;
typedef  char u_long ;
struct printf_info {int spec; char showsign; int prec; int width; scalar_t__ left; int /*<<< orphan*/  pad; scalar_t__ alt; scalar_t__ is_char; scalar_t__ is_short; scalar_t__ is_long; scalar_t__ is_ptrdiff; scalar_t__ is_size; scalar_t__ is_intmax; scalar_t__ is_quad; scalar_t__ is_long_double; scalar_t__ group; } ;
struct __printf_io {int dummy; } ;
struct TYPE_2__ {char* thousands_sep; char* grouping; } ;

/* Variables and functions */
 int BUF ; 
 char ULONG_MAX ; 
 char* __lowercase_hex ; 
 int /*<<< orphan*/  __printf_flush (struct __printf_io*) ; 
 scalar_t__ __printf_pad (struct __printf_io*,int,int) ; 
 scalar_t__ __printf_puts (struct __printf_io*,char const*,int) ; 
 char* __ujtoa (char,char*,int,char const*,int,char,char const*) ; 
 char* __ultoa (char,char*,int,char const*,int,char,char const*) ; 
 char* __uppercase_hex ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 TYPE_1__* localeconv () ; 
 int /*<<< orphan*/  stderr ; 

int
__printf_render_int(struct __printf_io *io, const struct printf_info *pi, const void *const *arg)
{
	const union arg *argp;
	char buf[BUF];
	char *p, *pe;
	char ns;
	int l, ngrp, rdx, sign, zext;
	const char *nalt, *digit;
	char thousands_sep;	/* locale specific thousands separator */
	const char *grouping;	/* locale specific numeric grouping rules */
	uintmax_t uu;
	int ret;

	ret = 0;
	nalt = NULL;
	digit = __lowercase_hex;
	ns = '\0';
	pe = buf + sizeof buf - 1;

	if (pi->group) {
		thousands_sep = *(localeconv()->thousands_sep);
		grouping = localeconv()->grouping;
		ngrp = 1;
	} else {
		thousands_sep = 0;
		grouping = NULL;
		ngrp = 0;
	}

	switch(pi->spec) {
	case 'd':
	case 'i':
		rdx = 10;
		sign = 1;
		break;
	case 'X':
		digit = __uppercase_hex;
		/*FALLTHOUGH*/
	case 'x':
		rdx = 16;
		sign = 0;
		break;
	case 'u':
	case 'U':
		rdx = 10;
		sign = 0;
		break;
	case 'o':
	case 'O':
		rdx = 8;
		sign = 0;
		break;
	default:
		fprintf(stderr, "pi->spec = '%c'\n", pi->spec);
		assert(1 == 0);
	}
	argp = arg[0];

	if (sign)
		ns = pi->showsign;

	if (pi->is_long_double || pi->is_quad || pi->is_intmax ||
	    pi->is_size || pi->is_ptrdiff) {
		if (sign && argp->intmaxarg < 0) {
			uu = -argp->intmaxarg;
			ns = '-';
		} else
			uu = argp->uintmaxarg;
	} else if (pi->is_long) {
		if (sign && argp->longarg < 0) {
			uu = (u_long)-argp->longarg;
			ns = '-';
		} else 
			uu = argp->ulongarg;
	} else if (pi->is_short) {
		if (sign && (short)argp->intarg < 0) {
			uu = -(short)argp->intarg;
			ns = '-';
		} else 
			uu = (unsigned short)argp->uintarg;
	} else if (pi->is_char) {
		if (sign && (signed char)argp->intarg < 0) {
			uu = -(signed char)argp->intarg;
			ns = '-';
		} else 
			uu = (unsigned char)argp->uintarg;
	} else {
		if (sign && argp->intarg < 0) {
			uu = (unsigned)-argp->intarg;
			ns = '-';
		} else
			uu = argp->uintarg;
	}
	if (uu <= ULONG_MAX)
		p = __ultoa(uu, pe, rdx, digit, ngrp, thousands_sep, grouping);
	else
		p = __ujtoa(uu, pe, rdx, digit, ngrp, thousands_sep, grouping);

	l = 0;
	if (uu == 0) {
		/*-
		 * ``The result of converting a zero value with an
		 * explicit precision of zero is no characters.''
		 *      -- ANSI X3J11
		 *
		 * ``The C Standard is clear enough as is.  The call
		 * printf("%#.0o", 0) should print 0.''
		 *      -- Defect Report #151
		 */
			;
		if (pi->prec == 0 && !(pi->alt && rdx == 8))
			p = pe;
	} else if (pi->alt) {
		if (rdx == 8) 
			*--p = '0';
		if (rdx == 16) {
			if (pi->spec == 'x')
				nalt = "0x";
			else
				nalt = "0X";
			l += 2;
		}
	}
	l += pe - p;
	if (ns)
		l++;

	/*-
	 * ``... diouXx conversions ... if a precision is
	 * specified, the 0 flag will be ignored.''
	 *      -- ANSI X3J11
	 */
	if (pi->prec > (pe - p))
		zext = pi->prec - (pe - p);
	else if (pi->prec != -1)
		zext = 0;
	else if (pi->pad == '0' && pi->width > l && !pi->left)
		zext = pi->width - l;
	else
		zext = 0;

	l += zext;

	while (zext > 0 && p > buf) {
		*--p = '0';
		zext--;
	}

	if (l < BUF) {
		if (ns) {
			*--p = ns;
		} else if (nalt != NULL) {
			*--p = nalt[1];
			*--p = nalt[0];
		}
		if (pi->width > (pe - p) && !pi->left) {
			l = pi->width - (pe - p);
			while (l > 0 && p > buf) {
				*--p = ' ';
				l--;
			}
			if (l)
				ret += __printf_pad(io, l, 0);
		}
	} else {
		if (!pi->left && pi->width > l)
			ret += __printf_pad(io, pi->width - l, 0);
		if (ns != '\0')
			ret += __printf_puts(io, &ns, 1);
		else if (nalt != NULL)
			ret += __printf_puts(io, nalt, 2);
		if (zext > 0)
			ret += __printf_pad(io, zext, 1);
	}
	
	ret += __printf_puts(io, p, pe - p);
	if (pi->width > ret && pi->left) 
		ret += __printf_pad(io, pi->width - ret, 0);
	__printf_flush(io);
	return (ret);
}