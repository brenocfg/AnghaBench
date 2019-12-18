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
typedef  int /*<<< orphan*/  uschar ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 int /*<<< orphan*/  EMPTYRE ; 
 int /*<<< orphan*/  FATAL (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NIL ; 
 int /*<<< orphan*/  dprintf (char*) ; 
 int /*<<< orphan*/ * lastre ; 
 int /*<<< orphan*/ * op2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * prestr ; 
 int /*<<< orphan*/ * regexp () ; 
 char relex () ; 
 char rtok ; 

Node *reparse(const char *p)	/* parses regular expression pointed to by p */
{			/* uses relex() to scan regular expression */
	Node *np;

	dprintf( ("reparse <%s>\n", p) );
	lastre = prestr = (uschar *) p;	/* prestr points to string to be parsed */
	rtok = relex();
	/* GNU compatibility: an empty regexp matches anything */
	if (rtok == '\0') {
		/* FATAL("empty regular expression"); previous */
		return(op2(EMPTYRE, NIL, NIL));
	}
	np = regexp();
	if (rtok != '\0')
		FATAL("syntax error in regular expression %s at %s", lastre, prestr);
	return(np);
}