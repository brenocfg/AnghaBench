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
struct tbl_opts {char const decimal; } ;
struct tbl_dat {char* string; } ;
struct rofftbl {size_t (* slen ) (char*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  arg; } ;
struct roffcol {size_t width; size_t decimal; size_t nwidth; } ;

/* Variables and functions */
 scalar_t__ isdigit (unsigned char) ; 
 size_t stub1 (char*,int /*<<< orphan*/ ) ; 
 size_t stub2 (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t
tblcalc_number(struct rofftbl *tbl, struct roffcol *col,
		const struct tbl_opts *opts, const struct tbl_dat *dp)
{
	const char	*cp, *lastdigit, *lastpoint;
	size_t		 intsz, totsz;
	char		 buf[2];

	if (dp->string == NULL || *dp->string == '\0')
		return 0;

	totsz = (*tbl->slen)(dp->string, tbl->arg);
	if (col == NULL)
		return totsz;

	/*
	 * Find the last digit and
	 * the last decimal point that is adjacent to a digit.
	 * The alignment indicator "\&" overrides everything.
	 */

	lastdigit = lastpoint = NULL;
	for (cp = dp->string; cp[0] != '\0'; cp++) {
		if (cp[0] == '\\' && cp[1] == '&') {
			lastdigit = lastpoint = cp;
			break;
		} else if (cp[0] == opts->decimal &&
		    (isdigit((unsigned char)cp[1]) ||
		     (cp > dp->string && isdigit((unsigned char)cp[-1]))))
			lastpoint = cp;
		else if (isdigit((unsigned char)cp[0]))
			lastdigit = cp;
	}

	/* Not a number, treat as a literal string. */

	if (lastdigit == NULL) {
		if (col != NULL && col->width < totsz)
			col->width = totsz;
		return totsz;
	}

	/* Measure the width of the integer part. */

	if (lastpoint == NULL)
		lastpoint = lastdigit + 1;
	intsz = 0;
	buf[1] = '\0';
	for (cp = dp->string; cp < lastpoint; cp++) {
		buf[0] = cp[0];
		intsz += (*tbl->slen)(buf, tbl->arg);
	}

	/*
         * If this number has more integer digits than all numbers
         * seen on earlier lines, shift them all to the right.
	 * If it has fewer, shift this number to the right.
	 */

	if (intsz > col->decimal) {
		col->nwidth += intsz - col->decimal;
		col->decimal = intsz;
	} else
		totsz += col->decimal - intsz;

	/* Update the maximum total width seen so far. */

	if (totsz > col->nwidth)
		col->nwidth = totsz;
	return totsz;
}