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
struct termp {int dummy; } ;
struct tbl_opts {char const decimal; } ;
struct tbl_dat {char* string; } ;
struct roffcol {size_t decimal; size_t width; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASCII_NBRSP ; 
 int /*<<< orphan*/  assert (char*) ; 
 scalar_t__ isdigit (unsigned char) ; 
 int /*<<< orphan*/  tbl_fill_char (struct termp*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  tbl_word (struct termp*,struct tbl_dat const*) ; 
 size_t term_strlen (struct termp*,char*) ; 

__attribute__((used)) static void
tbl_number(struct termp *tp, const struct tbl_opts *opts,
		const struct tbl_dat *dp,
		const struct roffcol *col)
{
	const char	*cp, *lastdigit, *lastpoint;
	size_t		 intsz, padl, totsz;
	char		 buf[2];

	/*
	 * Almost the same code as in tblcalc_number():
	 * First find the position of the decimal point.
	 */

	assert(dp->string);
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

	/* Then measure both widths. */

	padl = 0;
	totsz = term_strlen(tp, dp->string);
	if (lastdigit != NULL) {
		if (lastpoint == NULL)
			lastpoint = lastdigit + 1;
		intsz = 0;
		buf[1] = '\0';
		for (cp = dp->string; cp < lastpoint; cp++) {
			buf[0] = cp[0];
			intsz += term_strlen(tp, buf);
		}

		/*
		 * Pad left to match the decimal position,
		 * but avoid exceeding the total column width.
		 */

		if (col->decimal > intsz && col->width > totsz) {
			padl = col->decimal - intsz;
			if (padl + totsz > col->width)
				padl = col->width - totsz;
		}

	/* If it is not a number, simply center the string. */

	} else if (col->width > totsz)
		padl = (col->width - totsz) / 2;

	tbl_fill_char(tp, ASCII_NBRSP, padl);
	tbl_word(tp, dp);

	/* Pad right to fill the column.  */

	if (col->width > padl + totsz)
		tbl_fill_char(tp, ASCII_NBRSP, col->width - padl - totsz);
}