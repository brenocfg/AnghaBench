#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct tty {int dummy; } ;
struct TYPE_6__ {int status; TYPE_4__* sc; } ;
typedef  TYPE_1__ scr_stat ;
struct TYPE_7__ {scalar_t__ blink_in_progress; TYPE_1__* cur_scp; } ;

/* Variables and functions */
 int PCBURST ; 
 int /*<<< orphan*/  SC_VIDEO_LOCK (TYPE_4__*) ; 
 int /*<<< orphan*/  SC_VIDEO_UNLOCK (TYPE_4__*) ; 
 int SLKED ; 
 TYPE_1__* sc_get_stat (struct tty*) ; 
 int /*<<< orphan*/  sc_puts (TYPE_1__*,int /*<<< orphan*/ *,size_t) ; 
 size_t ttydisc_getc (struct tty*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
sctty_outwakeup(struct tty *tp)
{
    size_t len;
    u_char buf[PCBURST];
    scr_stat *scp = sc_get_stat(tp);

    if (scp->status & SLKED ||
	(scp == scp->sc->cur_scp && scp->sc->blink_in_progress))
	return;

    for (;;) {
	len = ttydisc_getc(tp, buf, sizeof buf);
	if (len == 0)
	    break;
	SC_VIDEO_LOCK(scp->sc);
	sc_puts(scp, buf, len);
	SC_VIDEO_UNLOCK(scp->sc);
    }
}