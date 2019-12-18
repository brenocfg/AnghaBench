#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ name; int id; } ;
struct TYPE_3__ {int /*<<< orphan*/  token; int /*<<< orphan*/ * collelem; int /*<<< orphan*/ * collsym; int /*<<< orphan*/  wc; } ;

/* Variables and functions */
 int EOF ; 
 int T_CHAR ; 
 scalar_t__ T_CHARMAP ; 
 int T_COLLELEM ; 
 int T_COLLSYM ; 
 scalar_t__ T_END ; 
 int T_NULL ; 
 int T_SYMBOL ; 
 int /*<<< orphan*/  add_tok (int) ; 
 scalar_t__ category ; 
 int esc_char ; 
 int escaped ; 
 int get_escaped (int) ; 
 int last_kw ; 
 int lookup_charmap (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lookup_collelem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lookup_collsym (int /*<<< orphan*/ *) ; 
 int scanc () ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  strdup (int /*<<< orphan*/ *) ; 
 TYPE_2__* symwords ; 
 int /*<<< orphan*/ * token ; 
 scalar_t__ tokidx ; 
 scalar_t__ toksz ; 
 int /*<<< orphan*/  yyerror (char*) ; 
 TYPE_1__ yylval ; 

int
get_symbol(void)
{
	int	c;

	while ((c = scanc()) != EOF) {
		if (escaped) {
			escaped = 0;
			if (c == '\n')
				continue;
			add_tok(get_escaped(c));
			continue;
		}
		if (c == esc_char) {
			escaped = 1;
			continue;
		}
		if (c == '\n') {	/* well that's strange! */
			yyerror("unterminated symbolic name");
			continue;
		}
		if (c == '>') {		/* end of symbol */

			/*
			 * This restarts the token from the beginning
			 * the next time we scan a character.  (This
			 * token is complete.)
			 */

			if (token == NULL) {
				yyerror("missing symbolic name");
				return (T_NULL);
			}
			tokidx = 0;

			/*
			 * A few symbols are handled as keywords outside
			 * of the normal categories.
			 */
			if (category == T_END) {
				int i;
				for (i = 0; symwords[i].name != 0; i++) {
					if (strcmp(token, symwords[i].name) ==
					    0) {
						last_kw = symwords[i].id;
						return (last_kw);
					}
				}
			}
			/*
			 * Contextual rule: Only literal characters are
			 * permitted in CHARMAP.  Anywhere else the symbolic
			 * forms are fine.
			 */
			if ((category != T_CHARMAP) &&
			    (lookup_charmap(token, &yylval.wc)) != -1) {
				return (T_CHAR);
			}
			if ((yylval.collsym = lookup_collsym(token)) != NULL) {
				return (T_COLLSYM);
			}
			if ((yylval.collelem = lookup_collelem(token)) !=
			    NULL) {
				return (T_COLLELEM);
			}
			/* its an undefined symbol */
			yylval.token = strdup(token);
			token = NULL;
			toksz = 0;
			tokidx = 0;
			return (T_SYMBOL);
		}
		add_tok(c);
	}

	yyerror("unterminated symbolic name");
	return (EOF);
}