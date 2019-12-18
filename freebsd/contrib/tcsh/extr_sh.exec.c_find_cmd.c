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
struct varent {char** vec; } ;
struct biltins {int /*<<< orphan*/  bname; } ;
typedef  char Char ;

/* Variables and functions */
 char* CGETS (int,int,char*) ; 
 int /*<<< orphan*/  STRautorehash ; 
 int /*<<< orphan*/  STRdot ; 
 int /*<<< orphan*/  STRpath ; 
 int /*<<< orphan*/  STRslash ; 
 char* Strspl (int /*<<< orphan*/ ,char*) ; 
 struct varent* adrof (int /*<<< orphan*/ ) ; 
 struct varent* adrof1 (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aliases ; 
 scalar_t__ any (int /*<<< orphan*/ ,char) ; 
 struct biltins const* bfunc ; 
 int /*<<< orphan*/  bit (int,int) ; 
 int /*<<< orphan*/  blkpr (char**) ; 
 int /*<<< orphan*/  cleanup_push (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup_until (char*) ; 
 int /*<<< orphan*/  dohash (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ eq (char*,int /*<<< orphan*/ ) ; 
 int executable (char*,char*,int /*<<< orphan*/ ) ; 
 int hash (int,int) ; 
 int hashdebug ; 
 int hashname (char*) ; 
 scalar_t__ havhash ; 
 size_t nbfunc ; 
 struct biltins const* nt_bfunc ; 
 size_t nt_nbfunc ; 
 int /*<<< orphan*/  short2str (char*) ; 
 int /*<<< orphan*/  str2short (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfree ; 
 int xhash ; 
 int /*<<< orphan*/  xprintf (char*,char*) ; 
 int /*<<< orphan*/  xputchar (char) ; 

int
find_cmd(Char *cmd, int prt)
{
    struct varent *var;
    const struct biltins *bptr;
    Char **pv;
    Char *sv;
    int hashval, rehashed, i, ex, rval = 0;

    if (prt && any(short2str(cmd), '/')) {
	xprintf("%s", CGETS(13, 7, "where: / in command makes no sense\n"));
	return rval;
    }

    /* first, look for an alias */

    if (prt && adrof1(cmd, &aliases)) {
	if ((var = adrof1(cmd, &aliases)) != NULL) {
	    xprintf(CGETS(13, 8, "%S is aliased to "), cmd);
	    if (var->vec != NULL)
		blkpr(var->vec);
	    xputchar('\n');
	    rval = 1;
	}
    }

    /* next, look for a shell builtin */

    for (bptr = bfunc; bptr < &bfunc[nbfunc]; bptr++) {
	if (eq(cmd, str2short(bptr->bname))) {
	    rval = 1;
	    if (prt)
		xprintf(CGETS(13, 9, "%S is a shell built-in\n"), cmd);
	    else
		return rval;
	}
    }
#ifdef WINNT_NATIVE
    for (bptr = nt_bfunc; bptr < &nt_bfunc[nt_nbfunc]; bptr++) {
	if (eq(cmd, str2short(bptr->bname))) {
	    rval = 1;
	    if (prt)
		xprintf(CGETS(13, 9, "%S is a shell built-in\n"), cmd);
	    else
		return rval;
	}
    }
#endif /* WINNT_NATIVE*/

    /* last, look through the path for the command */

    if ((var = adrof(STRpath)) == NULL)
	return rval;

    hashval = havhash ? hashname(cmd) : 0;

    sv = Strspl(STRslash, cmd);
    cleanup_push(sv, xfree);

    rehashed = 0;
retry:
    for (pv = var->vec, i = 0; pv && *pv; pv++, i++) {
	if (havhash && !eq(*pv, STRdot)) {
#ifdef FASTHASH
	    if (!bit(hashval, i))
		continue;
#else /* OLDHASH */
	    int hashval1 = hash(hashval, i);
	    if (!bit(xhash, hashval1))
		continue;
#endif /* FASTHASH */
	}
	ex = executable(*pv, sv, 0);
#ifdef FASTHASH
	if (!ex && (hashdebug & 2)) {
	    xprintf("%s", CGETS(13, 10, "hash miss: "));
	    ex = 1;	/* Force printing */
	}
#endif /* FASTHASH */
	if (ex) {
	    rval = 1;
	    if (prt) {
		xprintf("%S/", *pv);
		xprintf("%S\n", cmd);
	    }
	    else
		return rval;
	}
    }
    /*
     * If we are printing, we are being called from dowhere() which it 
     * has rehashed already
     */
    if (!prt && adrof(STRautorehash) && !rehashed && havhash) {
	dohash(NULL, NULL);
	rehashed = 1;
	goto retry;
    }
    cleanup_until(sv);
    return rval;
}