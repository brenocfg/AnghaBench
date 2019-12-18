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
 int GLOBSPACE ; 
 char* Strend (char const*) ; 
 char* Strsave (char const*) ; 
 int /*<<< orphan*/  blk_indirect_cleanup ; 
 int /*<<< orphan*/  cleanup_push (char***,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup_until (char***) ; 
 int /*<<< orphan*/  expbrace (char***,int /*<<< orphan*/ *,int) ; 
 int t_pmatch (char const*,char*,char const**,int) ; 
 void* xmalloc (int) ; 

int
Gnmatch(const Char *string, const Char *pattern, const Char **endstr)
{
    Char ***fblk, **p;
    const Char *tstring = string;
    int	   gpol = 1, gres = 0;

    if (*pattern == '^') {
	gpol = 0;
	pattern++;
    }

    fblk = xmalloc(sizeof(Char ***));
    *fblk = xmalloc(GLOBSPACE * sizeof(Char *));
    (*fblk)[0] = Strsave(pattern);
    (*fblk)[1] = NULL;

    cleanup_push(fblk, blk_indirect_cleanup);
    expbrace(fblk, NULL, GLOBSPACE);

    if (endstr == NULL)
	/* Exact matches only */
	for (p = *fblk; *p; p++) 
	    gres |= t_pmatch(string, *p, &tstring, 1) == 2 ? 1 : 0;
    else {
	const Char *end;

	/* partial matches */
        end = Strend(string);
	for (p = *fblk; *p; p++)
	    if (t_pmatch(string, *p, &tstring, 1) != 0) {
		gres |= 1;
		if (end > tstring)
		    end = tstring;
	    }
	*endstr = end;
    }

    cleanup_until(fblk);
    return(gres == gpol);
}