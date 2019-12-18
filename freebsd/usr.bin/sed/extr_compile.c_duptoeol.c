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
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  fname ; 
 int isspace (unsigned char) ; 
 int /*<<< orphan*/  linenum ; 
 char* malloc (size_t) ; 
 char* memmove (char*,char*,size_t) ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static char *
duptoeol(char *s, const char *ctype)
{
	size_t len;
	int ws;
	char *p, *start;

	ws = 0;
	for (start = s; *s != '\0' && *s != '\n'; ++s)
		ws = isspace((unsigned char)*s);
	*s = '\0';
	if (ws)
		warnx("%lu: %s: whitespace after %s", linenum, fname, ctype);
	len = s - start + 1;
	if ((p = malloc(len)) == NULL)
		err(1, "malloc");
	return (memmove(p, start, len));
}