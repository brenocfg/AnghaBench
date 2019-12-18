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
struct consdev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* te_term ) (int /*<<< orphan*/ *,void**) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  SC_KERNEL_CONSOLE ; 
 int /*<<< orphan*/  free (void*,int /*<<< orphan*/ ) ; 
 int mp_maxid ; 
 int /*<<< orphan*/  sc_clear_screen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sc_console ; 
 int sc_console_unit ; 
 int /*<<< orphan*/ ** sc_kts ; 
 TYPE_1__* sc_ktsw ; 
 int /*<<< orphan*/  sccnupdate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scterm (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,void**) ; 

__attribute__((used)) static void
sc_cnterm(struct consdev *cp)
{
    void *ts;
    int i;

    /* we are not the kernel console any more, release everything */

    if (sc_console_unit < 0)
	return;			/* shouldn't happen */

#if 0 /* XXX */
    sc_clear_screen(sc_console);
    sccnupdate(sc_console);
#endif

    if (sc_ktsw != NULL) {
	for (i = 0; i <= mp_maxid; i++) {
	    ts = sc_kts[i];
	    sc_kts[i] = NULL;
	    (*sc_ktsw->te_term)(sc_console, &ts);
	    free(ts, M_DEVBUF);
	}
	sc_ktsw = NULL;
    }
    scterm(sc_console_unit, SC_KERNEL_CONSOLE);
    sc_console_unit = -1;
    sc_console = NULL;
}