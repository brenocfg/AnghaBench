#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  l; int /*<<< orphan*/ * r; } ;
struct s_addr {scalar_t__ type; TYPE_1__ u; } ;

/* Variables and functions */
 scalar_t__ AT_LAST ; 
 scalar_t__ AT_LINE ; 
 scalar_t__ AT_RE ; 
 scalar_t__ AT_RELLINE ; 
 int /*<<< orphan*/  _POSIX2_LINE_MAX ; 
 char* compile_delimited (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * compile_re (char*,int) ; 
 int /*<<< orphan*/  errx (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fname ; 
 int /*<<< orphan*/  linenum ; 
 int /*<<< orphan*/  strtol (char*,char**,int) ; 

__attribute__((used)) static char *
compile_addr(char *p, struct s_addr *a)
{
	char *end, re[_POSIX2_LINE_MAX + 1];
	int icase;

	icase = 0;

	a->type = 0;
	switch (*p) {
	case '\\':				/* Context address */
		++p;
		/* FALLTHROUGH */
	case '/':				/* Context address */
		p = compile_delimited(p, re, 0);
		if (p == NULL)
			errx(1, "%lu: %s: unterminated regular expression", linenum, fname);
		/* Check for case insensitive regexp flag */
		if (*p == 'I') {
			icase = 1;
			p++;
		}
		if (*re == '\0')
			a->u.r = NULL;
		else
			a->u.r = compile_re(re, icase);
		a->type = AT_RE;
		return (p);

	case '$':				/* Last line */
		a->type = AT_LAST;
		return (p + 1);

	case '+':				/* Relative line number */
		a->type = AT_RELLINE;
		p++;
		/* FALLTHROUGH */
						/* Line number */
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
		if (a->type == 0)
			a->type = AT_LINE;
		a->u.l = strtol(p, &end, 10);
		return (end);
	default:
		errx(1, "%lu: %s: expected context address", linenum, fname);
		return (NULL);
	}
}