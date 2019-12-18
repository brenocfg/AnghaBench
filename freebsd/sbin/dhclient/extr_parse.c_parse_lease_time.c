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
typedef  int /*<<< orphan*/  time_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int NUMBER ; 
 int /*<<< orphan*/  convert_num (unsigned char*,char*,int,int) ; 
 int next_token (char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_semi (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_warn (char*) ; 
 int /*<<< orphan*/  skip_to_semi (int /*<<< orphan*/ *) ; 

void
parse_lease_time(FILE *cfile, time_t *timep)
{
	char *val;
	int token;

	token = next_token(&val, cfile);
	if (token != NUMBER) {
		parse_warn("Expecting numeric lease time");
		skip_to_semi(cfile);
		return;
	}
	convert_num((unsigned char *)timep, val, 10, 32);
	/* Unswap the number - convert_num returns stuff in NBO. */
	*timep = ntohl(*timep); /* XXX */

	parse_semi(cfile);
}