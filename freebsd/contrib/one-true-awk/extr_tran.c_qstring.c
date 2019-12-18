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
typedef  int uschar ;

/* Variables and functions */
 int /*<<< orphan*/  FATAL (char*,int*) ; 
 int /*<<< orphan*/  SYNTAX (char*,char const*) ; 
 int /*<<< orphan*/  isdigit (int) ; 
 scalar_t__ malloc (scalar_t__) ; 
 scalar_t__ strlen (char const*) ; 

char *qstring(const char *is, int delim)	/* collect string up to next delim */
{
	const char *os = is;
	int c, n;
	uschar *s = (uschar *) is;
	uschar *buf, *bp;

	if ((buf = (uschar *) malloc(strlen(is)+3)) == NULL)
		FATAL( "out of space in qstring(%s)", s);
	for (bp = buf; (c = *s) != delim; s++) {
		if (c == '\n')
			SYNTAX( "newline in string %.20s...", os );
		else if (c != '\\')
			*bp++ = c;
		else {	/* \something */
			c = *++s;
			if (c == 0) {	/* \ at end */
				*bp++ = '\\';
				break;	/* for loop */
			}	
			switch (c) {
			case '\\':	*bp++ = '\\'; break;
			case 'n':	*bp++ = '\n'; break;
			case 't':	*bp++ = '\t'; break;
			case 'b':	*bp++ = '\b'; break;
			case 'f':	*bp++ = '\f'; break;
			case 'r':	*bp++ = '\r'; break;
			default:
				if (!isdigit(c)) {
					*bp++ = c;
					break;
				}
				n = c - '0';
				if (isdigit(s[1])) {
					n = 8 * n + *++s - '0';
					if (isdigit(s[1]))
						n = 8 * n + *++s - '0';
				}
				*bp++ = n;
				break;
			}
		}
	}
	*bp++ = 0;
	return (char *) buf;
}