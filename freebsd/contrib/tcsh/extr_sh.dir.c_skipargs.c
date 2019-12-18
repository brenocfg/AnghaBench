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
 int DIR_LINE ; 
 int DIR_LONG ; 
 int DIR_OLD ; 
 int DIR_PRINT ; 
 int DIR_VERT ; 
 int /*<<< orphan*/  ERR_DIRUS ; 
 int /*<<< orphan*/  short2str (char*) ; 
 int /*<<< orphan*/  stderror (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,char const*) ; 
 char* strchr (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
skipargs(Char ***v, const char *dstr, const char *str)
{
    Char  **n = *v, *s;

    int dflag = 0, loop = 1;
    for (n++; loop && *n != NULL && (*n)[0] == '-'; n++) 
	if (*(s = &((*n)[1])) == '\0')	/* test for bare "-" argument */
	    dflag |= DIR_OLD;
	else if ((*n)[1] == '-' && (*n)[2] == '\0') {   /* test for -- */
	    n++;
	    break;
	} else {
	    char *p;
	    while (*s != '\0')	/* examine flags */ {
		if ((p = strchr(dstr, *s++)) != NULL)
		    dflag |= (1 << (p - dstr));
	        else
		    stderror(ERR_DIRUS, short2str(**v), dstr, str);
	    }
	}
    if (*n && (dflag & DIR_OLD))
	stderror(ERR_DIRUS, short2str(**v), dstr, str);
    *v = n;
    /* make -l, -v, and -n imply -p */
    if (dflag & (DIR_LONG|DIR_VERT|DIR_LINE))
	dflag |= DIR_PRINT;
    return dflag;
}