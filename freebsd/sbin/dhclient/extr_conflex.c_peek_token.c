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
 int get_token (int /*<<< orphan*/ *) ; 
 int lexchar ; 
 int lexline ; 
 int /*<<< orphan*/  prev_line ; 
 int tline ; 
 int tlpos ; 
 int token ; 
 int /*<<< orphan*/  token_line ; 
 char* tval ; 

int
peek_token(char **rval, FILE *cfile)
{
	int	x;

	if (!token) {
		tlpos = lexchar;
		tline = lexline;
		token = get_token(cfile);
		if (lexline != tline)
			token_line = prev_line;
		x = lexchar;
		lexchar = tlpos;
		tlpos = x;
		x = lexline;
		lexline = tline;
		tline = x;
	}
	if (rval)
		*rval = tval;

	return (token);
}