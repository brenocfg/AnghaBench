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
typedef  char eChar ;
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 char DEOF ; 
 char DgetC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_BADMOD ; 
 int /*<<< orphan*/  ERR_BADSUBST ; 
 int INT_MAX ; 
 scalar_t__ Isdigit (char) ; 
 int /*<<< orphan*/  Strbuf_append1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ any (char*,char) ; 
 int dol_flag_a ; 
 int dolmcnt ; 
 int /*<<< orphan*/  dolmod ; 
 scalar_t__ letter (char) ; 
 int /*<<< orphan*/  seterror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderror (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  unDredc (char) ; 

__attribute__((used)) static void
fixDolMod(void)
{
    eChar c;

    c = DgetC(0);
    if (c == ':') {
	do {
	    c = DgetC(0), dolmcnt = 1, dol_flag_a = 0;
	    if (c == 'g' || c == 'a') {
		if (c == 'g')
		    dolmcnt = INT_MAX;
		else
		    dol_flag_a = 1;
		c = DgetC(0);
	    }
	    if ((c == 'g' && dolmcnt != INT_MAX) || 
		(c == 'a' && dol_flag_a == 0)) {
		if (c == 'g')
		    dolmcnt = INT_MAX;
		else
		    dol_flag_a = 1;
		c = DgetC(0);
	    }

	    if (c == 's') {	/* [eichin:19910926.0755EST] */
		int delimcnt = 2;
		eChar delim = DgetC(0);
		Strbuf_append1(&dolmod, (Char) c);
		Strbuf_append1(&dolmod, (Char) delim);

		if (delim == DEOF || !delim || letter(delim)
		    || Isdigit(delim) || any(" \t\n", delim)) {
		    seterror(ERR_BADSUBST);
		    break;
		}	
		while ((c = DgetC(0)) != DEOF) {
		    Strbuf_append1(&dolmod, (Char) c);
		    if(c == delim) delimcnt--;
		    if(!delimcnt) break;
		}
		if(delimcnt) {
		    seterror(ERR_BADSUBST);
		    break;
		}
		continue;
	    }
	    if (!any("luhtrqxes", c))
		stderror(ERR_BADMOD, (int)c);
	    Strbuf_append1(&dolmod, (Char) c);
	    if (c == 'q')
		dolmcnt = INT_MAX;
	}
	while ((c = DgetC(0)) == ':');
	unDredc(c);
    }
    else
	unDredc(c);
}