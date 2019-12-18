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
typedef  int /*<<< orphan*/ * ndptr ;

/* Variables and functions */
 int /*<<< orphan*/  CHRSAVE (int) ; 
 int EOF ; 
 char EOS ; 
 int MAXTOK ; 
 int /*<<< orphan*/  PUSHBACK (int) ; 
 char* ep ; 
 int gpbc () ; 
 scalar_t__ isalnum (int) ; 
 int /*<<< orphan*/ * macro_getdef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  macros ; 
 int /*<<< orphan*/ * ohash_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ohash_qlookupi (int /*<<< orphan*/ *,char*,char const**) ; 
 int /*<<< orphan*/  outputstr (char*) ; 
 int /*<<< orphan*/  reallyputchar (int) ; 
 scalar_t__ sp ; 

__attribute__((used)) static ndptr
inspect(int c, char *tp)
{
	char *name = tp;
	char *etp = tp+MAXTOK;
	ndptr p;

	*tp++ = c;

	while ((isalnum(c = gpbc()) || c == '_') && tp < etp)
		*tp++ = c;
	if (c != EOF)
		PUSHBACK(c);
	*tp = EOS;
	/* token is too long, it won't match anything, but it can still
	 * be output. */
	if (tp == ep) {
		outputstr(name);
		while (isalnum(c = gpbc()) || c == '_') {
			if (sp < 0)
				reallyputchar(c);
			else
				CHRSAVE(c);
		}
		*name = EOS;
		return NULL;
	}

	p = ohash_find(&macros, ohash_qlookupi(&macros, name, (const char **)&tp));
	if (p == NULL)
		return NULL;
	if (macro_getdef(p) == NULL)
		return NULL;
	return p;
}