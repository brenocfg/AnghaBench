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
typedef  int ssize_t ;
typedef  int ptrdiff_t ;
struct TYPE_2__ {size_t len; char* s; } ;
typedef  char Char ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_BADSUBST ; 
 int /*<<< orphan*/  ERR_OLD ; 
 scalar_t__ INT_MAX ; 
 scalar_t__ Isdigit (char) ; 
 char* STRNULL ; 
 scalar_t__ Strcmp (char*,char*) ; 
 int /*<<< orphan*/  Strcpy (char*,char*) ; 
 int Strlen (char*) ; 
 int /*<<< orphan*/  Strncpy (char*,char*,int) ; 
 char* Strsave (char*) ; 
 char* Strstr (char*,char*) ; 
 int /*<<< orphan*/  addla (char*) ; 
 scalar_t__ any (char*,char) ; 
 scalar_t__ dol_flag_a ; 
 scalar_t__ dolmcnt ; 
 TYPE_1__ dolmod ; 
 char* dolp ; 
 char* domod (char*,char) ; 
 scalar_t__ letter (char) ; 
 scalar_t__ seterr ; 
 int /*<<< orphan*/  seterror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strip (char*) ; 
 int /*<<< orphan*/  xfree (char*) ; 
 char* xmalloc (size_t) ; 

__attribute__((used)) static void
setDolp(Char *cp)
{
    Char *dp;
    size_t i;

    if (dolmod.len == 0 || dolmcnt == 0) {
	dolp = cp;
	return;
    }
    cp = Strsave(cp);
    for (i = 0; i < dolmod.len; i++) {
	int didmod = 0;

	/* handle s// [eichin:19910926.0510EST] */
	if(dolmod.s[i] == 's') {
	    Char delim;
	    Char *lhsub, *rhsub, *np;
	    size_t lhlen = 0, rhlen = 0;

	    delim = dolmod.s[++i];
	    if (!delim || letter(delim)
		|| Isdigit(delim) || any(" \t\n", delim)) {
		seterror(ERR_BADSUBST);
		break;
	    }
	    lhsub = &dolmod.s[++i];
	    while(dolmod.s[i] != delim && dolmod.s[++i]) {
		lhlen++;
	    }
	    dolmod.s[i] = 0;
	    rhsub = &dolmod.s[++i];
	    while(dolmod.s[i] != delim && dolmod.s[++i]) {
		rhlen++;
	    }
	    dolmod.s[i] = 0;

	    strip(lhsub);
	    strip(rhsub);
	    strip(cp);
	    dp = cp;
	    do {
		dp = Strstr(dp, lhsub);
		if (dp) {
		    ptrdiff_t diff = dp - cp;
		    size_t len = (Strlen(cp) + 1 - lhlen + rhlen);
		    np = xmalloc(len * sizeof(Char));
		    (void) Strncpy(np, cp, diff);
		    (void) Strcpy(np + diff, rhsub);
		    (void) Strcpy(np + diff + rhlen, dp + lhlen);

		    xfree(cp);
		    dp = cp = np;
		    cp[--len] = '\0';
		    didmod = 1;
		    if (diff >= (ssize_t)len)
			break;
		} else {
		    /* should this do a seterror? */
		    break;
		}
	    }
	    while (dol_flag_a != 0);
	    /*
	     * restore dolmod for additional words
	     */
	    dolmod.s[i] = rhsub[-1] = (Char) delim;
        } else {

	    do {
		if ((dp = domod(cp, dolmod.s[i])) != NULL) {
		    didmod = 1;
		    if (Strcmp(cp, dp) == 0) {
			xfree(cp);
			cp = dp;
			break;
		    }
		    else {
			xfree(cp);
			cp = dp;
		    }
		}
		else
		    break;
	    }
	    while (dol_flag_a != 0);
	}
	if (didmod && dolmcnt != INT_MAX)
	    dolmcnt--;
#ifdef notdef
	else
	    break;
#endif
    }

    addla(cp);

    dolp = STRNULL;
    if (seterr)
	stderror(ERR_OLD);
}