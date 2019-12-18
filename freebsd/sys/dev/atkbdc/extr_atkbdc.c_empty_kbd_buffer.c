#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  kbd; int /*<<< orphan*/  aux; } ;
typedef  int /*<<< orphan*/  KBDC ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int KBDD_DELAYTIME ; 
 int KBDS_ANY_BUFFER_FULL ; 
 int KBDS_AUX_BUFFER_FULL ; 
 int KBDS_BUFFER_FULL ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  addq (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  emptyq (int /*<<< orphan*/ *) ; 
 TYPE_1__* kbdcp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*,int,int) ; 
 int read_data (TYPE_1__*) ; 
 int read_status (TYPE_1__*) ; 

void
empty_kbd_buffer(KBDC p, int wait)
{
    int t;
    int b;
    int f;
#if KBDIO_DEBUG >= 2
    int c1 = 0;
    int c2 = 0;
#endif
    int delta = 2;

    for (t = wait; t > 0; ) { 
        if ((f = read_status(kbdcp(p))) & KBDS_ANY_BUFFER_FULL) {
	    DELAY(KBDD_DELAYTIME);
            b = read_data(kbdcp(p));
	    if ((f & KBDS_BUFFER_FULL) == KBDS_AUX_BUFFER_FULL) {
		addq(&kbdcp(p)->aux, b);
#if KBDIO_DEBUG >= 2
		++c2;
            } else {
		++c1;
#endif
	    }
	    t = wait;
	} else {
	    t -= delta;
	}
        DELAY(delta*1000);
    }
#if KBDIO_DEBUG >= 2
    if ((c1 > 0) || (c2 > 0))
        log(LOG_DEBUG, "kbdc: %d:%d char read (empty_kbd_buffer)\n", c1, c2);
#endif

    emptyq(&kbdcp(p)->kbd);
}