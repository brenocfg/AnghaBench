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
struct varent {scalar_t__** vec; } ;
typedef  scalar_t__ Char ;

/* Variables and functions */
 scalar_t__ ABSOLUTEP (scalar_t__*) ; 
 int /*<<< orphan*/  STRautorehash ; 
 int /*<<< orphan*/  STRdot ; 
 int /*<<< orphan*/  STRpath ; 
 int /*<<< orphan*/  STRslash ; 
 scalar_t__* Strspl (int /*<<< orphan*/ ,scalar_t__*) ; 
 struct varent* adrof (int /*<<< orphan*/ ) ; 
 int any (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  bit (int,int) ; 
 int /*<<< orphan*/  dohash (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ eq (scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__ executable (scalar_t__*,scalar_t__*,int /*<<< orphan*/ ) ; 
 int hash (int,int) ; 
 int hashname (scalar_t__*) ; 
 scalar_t__ havhash ; 
 scalar_t__** justabs ; 
 int /*<<< orphan*/  short2str (scalar_t__*) ; 
 int /*<<< orphan*/  xfree (scalar_t__*) ; 
 int xhash ; 

__attribute__((used)) static int
iscommand(Char *name)
{
    Char **opv, **pv;
    Char *sav;
    struct varent *v;
    int slash = any(short2str(name), '/');
    int hashval, rehashed, i;

    v = adrof(STRpath);
    if (v == NULL || v->vec == NULL || v->vec[0] == NULL || slash)
	opv = justabs;
    else
	opv = v->vec;
    sav = Strspl(STRslash, name);	/* / command name for postpending */
    hashval = havhash ? hashname(name) : 0;

    rehashed = 0;
retry:
    pv = opv;
    i = 0;
    do {
	if (!slash && ABSOLUTEP(pv[0]) && havhash) {
#ifdef FASTHASH
	    if (!bit(hashval, i))
		goto cont;
#else /* OLDHASH */
	    int hashval1 = hash(hashval, i);
	    if (!bit(xhash, hashval1))
		goto cont;
#endif /* FASTHASH */
	}
	if (pv[0][0] == 0 || eq(pv[0], STRdot)) {	/* don't make ./xxx */
	    if (executable(NULL, name, 0)) {
		xfree(sav);
		return i + 1;
	    }
	}
	else {
	    if (executable(*pv, sav, 0)) {
		xfree(sav);
		return i + 1;
	    }
	}
cont:
	pv++;
	i++;
    } while (*pv);
    if (adrof(STRautorehash) && !rehashed && havhash && opv != justabs) {
	dohash(NULL, NULL);
	rehashed = 1;
	goto retry;
    }
    xfree(sav);
    return 0;
}