#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct sc_cnstate {scalar_t__ scr_opened; } ;
struct fkeytab {int len; int* str; } ;
struct TYPE_10__ {TYPE_5__* sc; TYPE_2__* tsw; } ;
typedef  TYPE_3__ scr_stat ;
struct TYPE_12__ {TYPE_1__* sc; } ;
struct TYPE_11__ {int /*<<< orphan*/  kbd; } ;
struct TYPE_9__ {int /*<<< orphan*/ * (* te_fkeystr ) (TYPE_3__*,int) ;} ;
struct TYPE_8__ {TYPE_3__* cur_scp; } ;

/* Variables and functions */
#define  ERRKEY 130 
#define  FKEY 129 
 int KEYCHAR (int) ; 
 int KEYFLAGS (int) ; 
#define  NOKEY 128 
 int SCGETC_CN ; 
 int SCGETC_NONBLOCK ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/  const*,int*,int) ; 
 int /*<<< orphan*/ * kbdd_get_fkeystr (int /*<<< orphan*/ ,int,size_t*) ; 
 TYPE_7__* sc_console ; 
 int /*<<< orphan*/  sc_touch_scrn_saver () ; 
 int /*<<< orphan*/  sccnupdate (TYPE_3__*) ; 
 int scgetc (TYPE_5__*,int,struct sc_cnstate*) ; 
 int strlen (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * stub1 (TYPE_3__*,int) ; 

__attribute__((used)) static int
sc_cngetc_locked(struct sc_cnstate *sp)
{
    static struct fkeytab fkey;
    static int fkeycp;
    scr_stat *scp;
    const u_char *p;
    int c;

    /* 
     * Stop the screen saver and update the screen if necessary.
     * What if we have been running in the screen saver code... XXX
     */
    if (sp->scr_opened)
	sc_touch_scrn_saver();
    scp = sc_console->sc->cur_scp;	/* XXX */
    if (sp->scr_opened)
	sccnupdate(scp);

    if (fkeycp < fkey.len)
	return fkey.str[fkeycp++];

    c = scgetc(scp->sc, SCGETC_CN | SCGETC_NONBLOCK, sp);

    switch (KEYFLAGS(c)) {
    case 0:	/* normal char */
	return KEYCHAR(c);
    case FKEY:	/* function key */
	p = (*scp->tsw->te_fkeystr)(scp, c);
	if (p != NULL) {
	    fkey.len = strlen(p);
	    bcopy(p, fkey.str, fkey.len);
	    fkeycp = 1;
	    return fkey.str[0];
	}
	p = kbdd_get_fkeystr(scp->sc->kbd, KEYCHAR(c), (size_t *)&fkeycp);
	fkey.len = fkeycp;
	if ((p != NULL) && (fkey.len > 0)) {
	    bcopy(p, fkey.str, fkey.len);
	    fkeycp = 1;
	    return fkey.str[0];
	}
	return c;	/* XXX */
    case NOKEY:
    case ERRKEY:
    default:
	return -1;
    }
    /* NOT REACHED */
}