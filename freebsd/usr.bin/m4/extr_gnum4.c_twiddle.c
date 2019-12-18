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
 int /*<<< orphan*/  addchar (char const) ; 
 int /*<<< orphan*/  addchars (char const*,int) ; 
 int /*<<< orphan*/  addconstantstring (char*) ; 
 char* getstring () ; 

__attribute__((used)) static char *
twiddle(const char *p)
{
	/* + at start of regexp is a normal character for Gnu m4 */
	if (*p == '^') {
		addchar(*p);
		p++;
	}
	if (*p == '+') {
		addchar('\\');
	}
	/* This could use strcspn for speed... */
	while (*p != '\0') {
		if (*p == '\\') {
			switch(p[1]) {
			case '(':
			case ')':
			case '|':
				addchar(p[1]);
				break;
			case 'w':
				addconstantstring("[_a-zA-Z0-9]");
				break;
			case 'W':
				addconstantstring("[^_a-zA-Z0-9]");
				break;
			case '<':
				addconstantstring("[[:<:]]");
				break;
			case '>':
				addconstantstring("[[:>:]]");
				break;
			default:
				addchars(p, 2);
				break;
			}
			p+=2;
			continue;
		}
		if (*p == '(' || *p == ')' || *p == '|')
			addchar('\\');

		addchar(*p);
		p++;
	}
	return getstring();
}