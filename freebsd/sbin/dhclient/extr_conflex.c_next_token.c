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
 int /*<<< orphan*/  cur_line ; 
 int get_token (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lexchar ; 
 scalar_t__ lexline ; 
 scalar_t__ tline ; 
 int /*<<< orphan*/  tlpos ; 
 int token ; 
 int /*<<< orphan*/  token_line ; 
 char* tval ; 

int
next_token(char **rval, FILE *cfile)
{
	int	rv;

	if (token) {
		if (lexline != tline)
			token_line = cur_line;
		lexchar = tlpos;
		lexline = tline;
		rv = token;
		token = 0;
	} else {
		rv = get_token(cfile);
		token_line = cur_line;
	}
	if (rval)
		*rval = tval;

	return (rv);
}