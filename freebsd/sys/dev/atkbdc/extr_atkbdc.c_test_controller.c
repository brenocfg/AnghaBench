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
struct TYPE_2__ {int /*<<< orphan*/  kbd; } ;
typedef  int /*<<< orphan*/  KBDC ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int FALSE ; 
 int /*<<< orphan*/  KBDC_DIAGNOSE ; 
 int KBD_DIAG_DONE ; 
 int KBD_DIAG_FAIL ; 
 int KBD_MAXRETRY ; 
 int KBD_MAXWAIT ; 
 int KBD_RESETDELAY ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  empty_both_buffers (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  emptyq (int /*<<< orphan*/ *) ; 
 TYPE_1__* kbdcp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*,int) ; 
 int read_controller_data (int /*<<< orphan*/ ) ; 
 scalar_t__ verbose ; 
 scalar_t__ write_controller_command (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
test_controller(KBDC p)
{
    int retry = KBD_MAXRETRY;
    int again = KBD_MAXWAIT;
    int c = KBD_DIAG_FAIL;

    while (retry-- > 0) {
        empty_both_buffers(p, 10);
        if (write_controller_command(p, KBDC_DIAGNOSE))
    	    break;
    }
    if (retry < 0)
        return FALSE;

    emptyq(&kbdcp(p)->kbd);
    while (again-- > 0) {
        /* wait awhile */
        DELAY(KBD_RESETDELAY*1000);
        c = read_controller_data(p);	/* DIAG_DONE/DIAG_FAIL */
        if (c != -1) 	/* wait again if the controller is not ready */
    	    break;
    }
    if (verbose || bootverbose)
        log(LOG_DEBUG, "kbdc: DIAGNOSE status:%04x\n", c);
    return (c == KBD_DIAG_DONE);
}