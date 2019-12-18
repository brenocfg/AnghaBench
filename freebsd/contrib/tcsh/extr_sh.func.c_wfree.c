#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int type; scalar_t__ a_seek; scalar_t__ f_seek; } ;
struct TYPE_3__ {int type; scalar_t__ a_seek; scalar_t__ f_seek; } ;
struct whyle {TYPE_2__ w_end; TYPE_1__ w_start; struct whyle* w_next; } ;
struct Ain {int type; scalar_t__ a_seek; scalar_t__ f_seek; } ;

/* Variables and functions */
 int TCSH_F_SEEK ; 
 int TCSH_I_SEEK ; 
 int /*<<< orphan*/  btell (struct Ain*) ; 
 struct whyle* whyles ; 
 int /*<<< orphan*/  wpfree (struct whyle*) ; 
 int /*<<< orphan*/  xprintf (char*,char const,scalar_t__,scalar_t__) ; 

void
wfree(void)
{
    struct Ain    o;
    struct whyle *nwp;
#ifdef lint
    nwp = NULL;	/* sun lint is dumb! */
#endif

#ifdef FDEBUG
    static const char foo[] = "IAFE";
#endif /* FDEBUG */

    btell(&o);

#ifdef FDEBUG
    xprintf("o->type %c o->a_seek %d o->f_seek %d\n",
	    foo[o.type + 1], o.a_seek, o.f_seek);
#endif /* FDEBUG */

    for (; whyles; whyles = nwp) {
	struct whyle *wp = whyles;
	nwp = wp->w_next;

#ifdef FDEBUG
	xprintf("start->type %c start->a_seek %d start->f_seek %d\n",
		foo[wp->w_start.type+1], 
		wp->w_start.a_seek, wp->w_start.f_seek);
	xprintf("end->type %c end->a_seek %d end->f_seek %d\n",
		foo[wp->w_end.type + 1], wp->w_end.a_seek, wp->w_end.f_seek);
#endif /* FDEBUG */

	/*
	 * XXX: We free loops that have different seek types.
	 */
	if (wp->w_end.type != TCSH_I_SEEK && wp->w_start.type == wp->w_end.type &&
	    wp->w_start.type == o.type) {
	    if (wp->w_end.type == TCSH_F_SEEK) {
		if (o.f_seek >= wp->w_start.f_seek && 
		    (wp->w_end.f_seek == 0 || o.f_seek < wp->w_end.f_seek))
		    break;
	    }
	    else {
		if (o.a_seek >= wp->w_start.a_seek && 
		    (wp->w_end.a_seek == 0 || o.a_seek < wp->w_end.a_seek))
		    break;
	    }
	}

	wpfree(wp);
    }
}