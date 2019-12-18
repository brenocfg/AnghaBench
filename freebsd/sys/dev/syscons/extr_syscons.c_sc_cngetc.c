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
struct sc_cnstate {int /*<<< orphan*/  kbd_opened; } ;
struct consdev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  sc; } ;

/* Variables and functions */
 int sc_cngetc_locked (struct sc_cnstate*) ; 
 TYPE_1__* sc_console ; 
 int /*<<< orphan*/  sccnclose (int /*<<< orphan*/ ,struct sc_cnstate*) ; 
 int /*<<< orphan*/  sccnopen (int /*<<< orphan*/ ,struct sc_cnstate*,int) ; 
 int spltty () ; 
 int /*<<< orphan*/  splx (int) ; 

__attribute__((used)) static int
sc_cngetc(struct consdev *cd)
{
    struct sc_cnstate st;
    int c, s;

    /* assert(sc_console != NULL) */
    sccnopen(sc_console->sc, &st, 1);
    s = spltty();	/* block sckbdevent and scrn_timer while we poll */
    if (!st.kbd_opened) {
	splx(s);
	sccnclose(sc_console->sc, &st);
	return -1;	/* means no keyboard since we fudged the locking */
    }
    c = sc_cngetc_locked(&st);
    splx(s);
    sccnclose(sc_console->sc, &st);
    return c;
}