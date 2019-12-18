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
 int SEMI ; 
 int next_token (char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_warn (char*) ; 
 int /*<<< orphan*/  skip_to_semi (int /*<<< orphan*/ *) ; 

int
parse_semi(FILE *cfile)
{
	int token;
	char *val;

	token = next_token(&val, cfile);
	if (token != SEMI) {
		parse_warn("semicolon expected.");
		skip_to_semi(cfile);
		return (0);
	}
	return (1);
}