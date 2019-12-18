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
typedef  char Char ;

/* Variables and functions */
 int G_CSH ; 
 int G_GLOB ; 
 scalar_t__ ISDOTDOT (char const*) ; 
 scalar_t__ SYM_EXPAND ; 
 scalar_t__ isglob (char const) ; 
 scalar_t__ symlinks ; 

int
tglob(Char **t)
{
    int gflag;
    const Char *p;

    gflag = 0;
    while ((p = *t++) != NULL) {
	if (*p == '~' || *p == '=')
	    gflag |= G_CSH;
	else if (*p == '{' &&
		 (p[1] == '\0' || (p[1] == '}' && p[2] == '\0')))
	    continue;
	while (*p != '\0') {
	    if (*p == '`') {
		gflag |= G_CSH;
#ifdef notdef
		/*
		 * We do want to expand echo `echo '*'`, so we don't\
		 * use this piece of code anymore.
		 */
		p++;
		while (*p && *p != '`') 
		    if (*p++ == '\\') {
			if (*p)		/* Quoted chars */
			    p++;
			else
			    break;
		    }
		if (!*p)		/* The matching ` */
		    break;
#endif
	    }
	    else if (*p == '{')
		gflag |= G_CSH;
	    else if (isglob(*p))
		gflag |= G_GLOB;
	    else if (symlinks == SYM_EXPAND && 
		p[1] && ISDOTDOT(p) && (p == *(t-1) || *(p-1) == '/') )
	    	gflag |= G_CSH;
	    p++;
	}
    }
    return gflag;
}