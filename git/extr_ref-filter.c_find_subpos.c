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
 int parse_signature (char const*,unsigned long) ; 
 char* strchrnul (char const*,char) ; 
 unsigned long strlen (char const*) ; 

__attribute__((used)) static void find_subpos(const char *buf,
			const char **sub, unsigned long *sublen,
			const char **body, unsigned long *bodylen,
			unsigned long *nonsiglen,
			const char **sig, unsigned long *siglen)
{
	const char *eol;
	/* skip past header until we hit empty line */
	while (*buf && *buf != '\n') {
		eol = strchrnul(buf, '\n');
		if (*eol)
			eol++;
		buf = eol;
	}
	/* skip any empty lines */
	while (*buf == '\n')
		buf++;

	/* parse signature first; we might not even have a subject line */
	*sig = buf + parse_signature(buf, strlen(buf));
	*siglen = strlen(*sig);

	/* subject is first non-empty line */
	*sub = buf;
	/* subject goes to first empty line */
	while (buf < *sig && *buf && *buf != '\n') {
		eol = strchrnul(buf, '\n');
		if (*eol)
			eol++;
		buf = eol;
	}
	*sublen = buf - *sub;
	/* drop trailing newline, if present */
	if (*sublen && (*sub)[*sublen - 1] == '\n')
		*sublen -= 1;

	/* skip any empty lines */
	while (*buf == '\n')
		buf++;
	*body = buf;
	*bodylen = strlen(buf);
	*nonsiglen = *sig - buf;
}