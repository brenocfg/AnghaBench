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
struct sbuf {int dummy; } ;
typedef  int /*<<< orphan*/  locale_t ;
typedef  int analyzer_states ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
#define  DELIM_SEEN 133 
 int EOF ; 
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
#define  INIT 132 
#define  KEYWORD 131 
 int /*<<< orphan*/  LC_ALL_MASK ; 
#define  PUNC_SEEN 130 
#define  PUNC_SEEN_SVN 129 
#define  TEXT 128 
 int fgetc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char const*) ; 
 int /*<<< orphan*/  freelocale (int /*<<< orphan*/ ) ; 
 char* getprogname () ; 
 int /*<<< orphan*/  isalpha_l (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscntrl_l (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  newlocale (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int /*<<< orphan*/  sbuf_clear (struct sbuf*) ; 
 char* sbuf_data (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_delete (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_finish (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_len (struct sbuf*) ; 
 struct sbuf* sbuf_new_auto () ; 
 int /*<<< orphan*/  sbuf_putc (struct sbuf*,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
scan(FILE *fp, const char *name, bool quiet)
{
	int c;
	bool hasid = false;
	bool subversion = false;
	analyzer_states state = INIT;
	struct sbuf *id = sbuf_new_auto();
	locale_t l;

	l = newlocale(LC_ALL_MASK, "C", NULL);

	if (name != NULL)
		printf("%s:\n", name);

	while ((c = fgetc(fp)) != EOF) {
		switch (state) {
		case INIT:
			if (c == '$') {
				/* Transit to DELIM_SEEN if we see $ */
				state = DELIM_SEEN;
			} else {
				/* Otherwise, stay in INIT state */
				continue;
			}
			break;
		case DELIM_SEEN:
			if (isalpha_l(c, l)) {
				/* Transit to KEYWORD if we see letter */
				sbuf_clear(id);
				sbuf_putc(id, '$');
				sbuf_putc(id, c);
				state = KEYWORD;

				continue;
			} else if (c == '$') {
				/* Or, stay in DELIM_SEEN if more $ */
				continue;
			} else {
				/* Otherwise, transit back to INIT */
				state = INIT;
			}
			break;
		case KEYWORD:
			sbuf_putc(id, c);

			if (isalpha_l(c, l)) {
				/*
				 * Stay in KEYWORD if additional letter is seen
				 */
				continue;
			} else if (c == ':') {
				/*
				 * See ':' for the first time, transit to
				 * PUNC_SEEN.
				 */
				state = PUNC_SEEN;
				subversion = false;
			} else if (c == '$') {
				/*
				 * Incomplete ident.  Go back to DELIM_SEEN
				 * state because we see a '$' which could be
				 * the beginning of a keyword.
				 */
				state = DELIM_SEEN;
			} else {
				/*
				 * Go back to INIT state otherwise.
				 */
				state = INIT;
			}
			break;
		case PUNC_SEEN:
		case PUNC_SEEN_SVN:
			sbuf_putc(id, c);

			switch (c) {
			case ':':
				/*
				 * If we see '::' (seen : in PUNC_SEEN),
				 * activate subversion treatment and transit
				 * to PUNC_SEEN_SVN state.
				 *
				 * If more than two :'s were seen, the ident
				 * is invalid and we would therefore go back
				 * to INIT state.
				 */
				if (state == PUNC_SEEN) {
					state = PUNC_SEEN_SVN;
					subversion = true;
				} else {
					state = INIT;
				}
				break;
			case ' ':
				/*
				 * A space after ':' or '::' indicates we are at the
				 * last component of potential ident.
				 */
				state = TEXT;
				break;
			default:
				/* All other characters are invalid */
				state = INIT;
				break;
			}
			break;
		case TEXT:
			sbuf_putc(id, c);

			if (iscntrl_l(c, l)) {
				/* Control characters are not allowed in this state */
				state = INIT;
			} else if (c == '$') {
				sbuf_finish(id);
				/*
				 * valid ident should end with a space.
				 *
				 * subversion extension uses '#' to indicate that
				 * the keyword expansion have exceeded the fixed
				 * width, so it is also permitted if we are in
				 * subversion mode.  No length check is enforced
				 * because GNU RCS ident(1) does not do it either.
				 */
				c = sbuf_data(id)[sbuf_len(id) - 2];
				if (c == ' ' || (subversion && c == '#')) {
					printf("     %s\n", sbuf_data(id));
					hasid = true;
				}
				state = INIT;
			}
			/* Other characters: stay in the state */
			break;
		}
	}
	sbuf_delete(id);
	freelocale(l);

	if (!hasid) {
		if (!quiet)
			fprintf(stderr, "%s warning: no id keywords in %s\n",
			    getprogname(), name ? name : "standard input");

		return (EXIT_FAILURE);
	}

	return (EXIT_SUCCESS);
}