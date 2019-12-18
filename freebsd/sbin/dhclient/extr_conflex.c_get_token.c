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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ eol_token ; 
 int get_char (int /*<<< orphan*/ *) ; 
 scalar_t__ isalpha (int) ; 
 scalar_t__ isascii (int) ; 
 scalar_t__ isdigit (int) ; 
 scalar_t__ isspace (int) ; 
 int lexchar ; 
 int lexline ; 
 int line ; 
 int lpos ; 
 int read_num_or_name (int,int /*<<< orphan*/ *) ; 
 int read_number (int,int /*<<< orphan*/ *) ; 
 int read_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip_to_eol (int /*<<< orphan*/ *) ; 
 char* tval ; 

__attribute__((used)) static int
get_token(FILE *cfile)
{
	int		c, ttok;
	static char	tb[2];
	int		l, p;

	do {
		l = line;
		p = lpos;

		c = get_char(cfile);

		if (!(c == '\n' && eol_token) && isascii(c) && isspace(c))
			continue;
		if (c == '#') {
			skip_to_eol(cfile);
			continue;
		}
		if (c == '"') {
			lexline = l;
			lexchar = p;
			ttok = read_string(cfile);
			break;
		}
		if ((isascii(c) && isdigit(c)) || c == '-') {
			lexline = l;
			lexchar = p;
			ttok = read_number(c, cfile);
			break;
		} else if (isascii(c) && isalpha(c)) {
			lexline = l;
			lexchar = p;
			ttok = read_num_or_name(c, cfile);
			break;
		} else {
			lexline = l;
			lexchar = p;
			tb[0] = c;
			tb[1] = 0;
			tval = tb;
			ttok = c;
			break;
		}
	} while (1);
	return (ttok);
}