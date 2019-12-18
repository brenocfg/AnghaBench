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
struct TYPE_2__ {int /*<<< orphan*/  aux; } ;
typedef  int /*<<< orphan*/  KBDC ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int FALSE ; 
 int KBD_MAXRETRY ; 
 int KBD_MAXWAIT ; 
 int KBD_RESETDELAY ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  PSMC_RESET_DEV ; 
 int PSM_ACK ; 
 int PSM_RESEND ; 
 int PSM_RESET_DONE ; 
 int TRUE ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  empty_both_buffers (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  emptyq (int /*<<< orphan*/ *) ; 
 TYPE_1__* kbdcp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*,int) ; 
 int read_aux_data (int /*<<< orphan*/ ) ; 
 int read_aux_data_no_wait (int /*<<< orphan*/ ) ; 
 scalar_t__ verbose ; 
 int /*<<< orphan*/  write_aux_command (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
reset_aux_dev(KBDC p)
{
    int retry = KBD_MAXRETRY;
    int again = KBD_MAXWAIT;
    int c = PSM_RESEND;		/* keep the compiler happy */

    while (retry-- > 0) {
        empty_both_buffers(p, 10);
        if (!write_aux_command(p, PSMC_RESET_DEV))
	    continue;
	emptyq(&kbdcp(p)->aux);
	/* NOTE: Compaq Armada laptops require extra delay here. XXX */
	for (again = KBD_MAXWAIT; again > 0; --again) {
            DELAY(KBD_RESETDELAY*1000);
            c = read_aux_data_no_wait(p);
	    if (c != -1)
		break;
	}
        if (verbose || bootverbose)
            log(LOG_DEBUG, "kbdc: RESET_AUX return code:%04x\n", c);
        if (c == PSM_ACK)	/* aux dev is about to reset... */
    	    break;
    }
    if (retry < 0)
        return FALSE;

    for (again = KBD_MAXWAIT; again > 0; --again) {
        /* wait awhile, well, quite looooooooooooong */
        DELAY(KBD_RESETDELAY*1000);
        c = read_aux_data_no_wait(p);	/* RESET_DONE/RESET_FAIL */
        if (c != -1) 	/* wait again if the controller is not ready */
    	    break;
    }
    if (verbose || bootverbose)
        log(LOG_DEBUG, "kbdc: RESET_AUX status:%04x\n", c);
    if (c != PSM_RESET_DONE)	/* reset status */
        return FALSE;

    c = read_aux_data(p);	/* device ID */
    if (verbose || bootverbose)
        log(LOG_DEBUG, "kbdc: RESET_AUX ID:%04x\n", c);
    /* NOTE: we could check the device ID now, but leave it later... */
    return TRUE;
}