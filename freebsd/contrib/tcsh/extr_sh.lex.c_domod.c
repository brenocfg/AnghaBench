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
typedef  int Char ;

/* Variables and functions */
 int* NLSChangeCase (int*,int) ; 
 int QUOTE ; 
 int* STRNULL ; 
 int* STRQNULL ; 
 int* Strend (int*) ; 
 int* Strnsave (int*,int) ; 
 int* Strrchr (int*,char) ; 
 int* Strsave (int*) ; 
 int /*<<< orphan*/  any (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  short2str (int*) ; 

Char   *
domod(Char *cp, Char type)
{
    Char *wp, *xp;
    int c;

    switch (type) {

    case 'q':
    case 'x':
	if (*cp == '\0')
	    return Strsave(STRQNULL);
	wp = Strsave(cp);
	for (xp = wp; (c = *xp) != 0; xp++)
	    if ((c != ' ' && c != '\t') || type == 'q')
		*xp |= QUOTE;
	return (wp);

    case 'l':
	wp = NLSChangeCase(cp, 1);
	return wp ? wp : Strsave(cp);

    case 'u':
	wp = NLSChangeCase(cp, 0);
	return wp ? wp : Strsave(cp);

    case 'h':
    case 't':
	if (!any(short2str(cp), '/'))
	    return (type == 't' ? Strsave(cp) : 0);
	wp = Strrchr(cp, '/');
	if (type == 'h')
	    xp = Strnsave(cp, wp - cp);
	else
	    xp = Strsave(wp + 1);
	return (xp);

    case 'e':
    case 'r':
	wp = Strend(cp);
	for (wp--; wp >= cp && *wp != '/'; wp--)
	    if (*wp == '.') {
		if (type == 'e')
		    xp = Strsave(wp + 1);
		else
		    xp = Strnsave(cp, wp - cp);
		return (xp);
	    }
	return (Strsave(type == 'e' ? STRNULL : cp));
    default:
	break;
    }
    return (0);
}