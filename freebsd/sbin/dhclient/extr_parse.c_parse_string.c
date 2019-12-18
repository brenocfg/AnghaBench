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
 int STRING ; 
 int /*<<< orphan*/  error (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 int next_token (char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_semi (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_warn (char*) ; 
 int /*<<< orphan*/  skip_to_semi (int /*<<< orphan*/ *) ; 
 int strlen (char*) ; 

char *
parse_string(FILE *cfile)
{
	char *val, *s;
	size_t valsize;
	int token;

	token = next_token(&val, cfile);
	if (token != STRING) {
		parse_warn("filename must be a string");
		skip_to_semi(cfile);
		return (NULL);
	}
	valsize = strlen(val) + 1;
	s = malloc(valsize);
	if (!s)
		error("no memory for string %s.", val);
	memcpy(s, val, valsize);

	if (!parse_semi(cfile)) {
		free(s);
		return (NULL);
	}
	return (s);
}