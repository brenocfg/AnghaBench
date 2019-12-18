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
 scalar_t__ iswhite (char) ; 

int
gv_tokenize(char *cptr, char *token[], int maxtoken)
{
	int tokennr;	/* Index of this token. */
	char delim;	/* Delimiter for searching for the partner. */
	
	for (tokennr = 0; tokennr < maxtoken;) {

		/* Skip leading white space. */
		while (iswhite(*cptr))
			cptr++;

		/* End of line. */
		if ((*cptr == '\0') || (*cptr == '\n') || (*cptr == '#'))
			return tokennr;

		delim = *cptr;
		token[tokennr] = cptr;		/* Point to it. */
		tokennr++;			/* One more. */

		/* Run off the end? */
		if (tokennr == maxtoken)
			return tokennr;

		/* Quoted? */
		if ((delim == '\'') || (delim == '"')) {
			for (;;) {
				cptr++;

				/* Found the partner. */
				if ((*cptr == delim) && (cptr[-1] != '\\')) {
					cptr++;

					/* Space after closing quote needed. */
					if (!iswhite(*cptr))
						return -1;

					/* Delimit. */
					*cptr++ = '\0';

				/* End-of-line? */
				} else if ((*cptr == '\0') || (*cptr == '\n'))
					return -1;
			}

		/* Not quoted. */
		} else {
			while ((*cptr != '\0') &&
			    (!iswhite(*cptr)) &&
			    (*cptr != '\n'))
				cptr++;

			/* Not end-of-line; delimit and move to the next. */
			if (*cptr != '\0')
				*cptr++ = '\0';
		}
	}

	/* Can't get here. */
	return maxtoken;
}