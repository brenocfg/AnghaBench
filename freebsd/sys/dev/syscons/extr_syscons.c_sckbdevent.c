#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  char u_char ;
struct tty {int dummy; } ;
struct TYPE_8__ {int keyboard; TYPE_3__* cur_scp; int /*<<< orphan*/ * kbd; } ;
typedef  TYPE_2__ sc_softc_t ;
typedef  int /*<<< orphan*/  keyboard_t ;
struct TYPE_9__ {int /*<<< orphan*/  status; TYPE_1__* tsw; int /*<<< orphan*/  index; } ;
struct TYPE_7__ {char* (* te_fkeystr ) (TYPE_3__*,int) ;scalar_t__ (* te_input ) (TYPE_3__*,int,struct tty*) ;} ;

/* Variables and functions */
#define  BKEY 132 
 int EINVAL ; 
#define  FKEY 131 
 int /*<<< orphan*/  Giant ; 
#define  KBDIO_KEYINPUT 130 
#define  KBDIO_UNLOADING 129 
 int KEYCHAR (int) ; 
 int KEYFLAGS (int) ; 
#define  MKEY 128 
 int /*<<< orphan*/  MOUSE_HIDDEN ; 
 int NOKEY ; 
 int /*<<< orphan*/  SCGETC_NONBLOCK ; 
 struct tty* SC_DEV (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kbd_release (int /*<<< orphan*/ *,void*) ; 
 char* kbdd_get_fkeystr (int /*<<< orphan*/ *,int,size_t*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int scgetc (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int strlen (char const*) ; 
 scalar_t__ stub1 (TYPE_3__*,int,struct tty*) ; 
 char* stub2 (TYPE_3__*,int) ; 
 int /*<<< orphan*/  tty_opened_ns (struct tty*) ; 
 int /*<<< orphan*/  ttydisc_rint (struct tty*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttydisc_rint_done (struct tty*) ; 
 int /*<<< orphan*/  ttydisc_rint_simple (struct tty*,char const*,int) ; 

__attribute__((used)) static int
sckbdevent(keyboard_t *thiskbd, int event, void *arg)
{
    sc_softc_t *sc;
    struct tty *cur_tty;
    int c, error = 0; 
    size_t len;
    const u_char *cp;

    sc = (sc_softc_t *)arg;
    /* assert(thiskbd == sc->kbd) */

    mtx_lock(&Giant);

    switch (event) {
    case KBDIO_KEYINPUT:
	break;
    case KBDIO_UNLOADING:
	sc->kbd = NULL;
	sc->keyboard = -1;
	kbd_release(thiskbd, (void *)&sc->keyboard);
	goto done;
    default:
	error = EINVAL;
	goto done;
    }

    /* 
     * Loop while there is still input to get from the keyboard.
     * I don't think this is nessesary, and it doesn't fix
     * the Xaccel-2.1 keyboard hang, but it can't hurt.		XXX
     */
    while ((c = scgetc(sc, SCGETC_NONBLOCK, NULL)) != NOKEY) {

	cur_tty = SC_DEV(sc, sc->cur_scp->index);
	if (!tty_opened_ns(cur_tty))
	    continue;

	if ((*sc->cur_scp->tsw->te_input)(sc->cur_scp, c, cur_tty))
	    continue;

	switch (KEYFLAGS(c)) {
	case 0x0000: /* normal key */
	    ttydisc_rint(cur_tty, KEYCHAR(c), 0);
	    break;
	case FKEY:  /* function key, return string */
	    cp = (*sc->cur_scp->tsw->te_fkeystr)(sc->cur_scp, c);
	    if (cp != NULL) {
	    	ttydisc_rint_simple(cur_tty, cp, strlen(cp));
		break;
	    }
	    cp = kbdd_get_fkeystr(thiskbd, KEYCHAR(c), &len);
	    if (cp != NULL)
	    	ttydisc_rint_simple(cur_tty, cp, len);
	    break;
	case MKEY:  /* meta is active, prepend ESC */
	    ttydisc_rint(cur_tty, 0x1b, 0);
	    ttydisc_rint(cur_tty, KEYCHAR(c), 0);
	    break;
	case BKEY:  /* backtab fixed sequence (esc [ Z) */
	    ttydisc_rint_simple(cur_tty, "\x1B[Z", 3);
	    break;
	}

	ttydisc_rint_done(cur_tty);
    }

    sc->cur_scp->status |= MOUSE_HIDDEN;

done:
    mtx_unlock(&Giant);
    return (error);
}