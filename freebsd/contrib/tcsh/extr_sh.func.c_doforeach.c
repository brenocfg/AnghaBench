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
struct TYPE_2__ {int /*<<< orphan*/  type; } ;
struct whyle {char** w_fe; char** w_fe0; TYPE_1__ w_end; struct whyle* w_next; int /*<<< orphan*/  w_fename; int /*<<< orphan*/  w_start; } ;
struct command {int dummy; } ;
typedef  char Char ;

/* Variables and functions */
 int ERR_NAME ; 
 int ERR_NOMATCH ; 
 int ERR_NOPAREN ; 
 int ERR_VARALNUM ; 
 int ERR_VARBEGIN ; 
 int /*<<< orphan*/  Strsave (char*) ; 
 int /*<<< orphan*/  TCSH_F_SEEK ; 
 int /*<<< orphan*/  TC_FOREACH ; 
 int /*<<< orphan*/  USE (struct command*) ; 
 scalar_t__ alnum (char) ; 
 int blklen (char**) ; 
 int /*<<< orphan*/  btell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  doagain () ; 
 char** globall (char**,int) ; 
 scalar_t__ intty ; 
 int /*<<< orphan*/  letter (char) ; 
 int /*<<< orphan*/  noexec ; 
 int /*<<< orphan*/  preread () ; 
 char** saveblk (char**) ; 
 int /*<<< orphan*/  stderror (int) ; 
 char* strip (char*) ; 
 int tglob (char**) ; 
 int /*<<< orphan*/  trim (char**) ; 
 struct whyle* whyles ; 
 struct whyle* xcalloc (int,int) ; 
 int /*<<< orphan*/  zlast ; 

void
doforeach(Char **v, struct command *c)
{
    Char *cp, *sp;
    struct whyle *nwp;
    int gflag;

    USE(c);
    v++;
    cp = sp = strip(*v);
    if (!letter(*cp))
	stderror(ERR_NAME | ERR_VARBEGIN);
    do {
	cp++;
    } while (alnum(*cp));
    if (*cp != '\0')
	stderror(ERR_NAME | ERR_VARALNUM);
    cp = *v++;
    if (v[0][0] != '(' || v[blklen(v) - 1][0] != ')')
	stderror(ERR_NAME | ERR_NOPAREN);
    v++;
    gflag = tglob(v);
    if (gflag) {
	v = globall(v, gflag);
	if (v == 0 && !noexec)
	    stderror(ERR_NAME | ERR_NOMATCH);
    }
    else {
	v = saveblk(v);
	trim(v);
    }
    nwp = xcalloc(1, sizeof *nwp);
    nwp->w_fe = nwp->w_fe0 = v;
    btell(&nwp->w_start);
    nwp->w_fename = Strsave(cp);
    nwp->w_next = whyles;
    nwp->w_end.type = TCSH_F_SEEK;
    whyles = nwp;
    /*
     * Pre-read the loop so as to be more comprehensible to a terminal user.
     */
    zlast = TC_FOREACH;
    if (intty)
	preread();
    if (!noexec)
	doagain();
}