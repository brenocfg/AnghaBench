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
struct atkbdc_softc {int retry; int /*<<< orphan*/  kbd; int /*<<< orphan*/  aux; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KBDC_DELAYTIME ; 
 int /*<<< orphan*/  KBDD_DELAYTIME ; 
 int KBDS_ANY_BUFFER_FULL ; 
 int KBDS_AUX_BUFFER_FULL ; 
 int KBDS_BUFFER_FULL ; 
 int KBDS_KBD_BUFFER_FULL ; 
 int PSM_ACK ; 
 int PSM_RESEND ; 
 int PSM_RESET_FAIL ; 
 int /*<<< orphan*/  addq (int /*<<< orphan*/ *,int) ; 
 int read_data (struct atkbdc_softc*) ; 
 int read_status (struct atkbdc_softc*) ; 

__attribute__((used)) static int
wait_for_aux_ack(struct atkbdc_softc *kbdc)
{
    int retry;
    int f;
    int b;

    /* CPU will stay inside the loop for 200msec at most */
    retry = kbdc->retry * 2;

    while (retry-- > 0) {
        if ((f = read_status(kbdc)) & KBDS_ANY_BUFFER_FULL) {
	    DELAY(KBDD_DELAYTIME);
            b = read_data(kbdc);
	    if ((f & KBDS_BUFFER_FULL) == KBDS_AUX_BUFFER_FULL) {
		if ((b == PSM_ACK) || (b == PSM_RESEND) 
		    || (b == PSM_RESET_FAIL))
		    return b;
		addq(&kbdc->aux, b);
	    } else if ((f & KBDS_BUFFER_FULL) == KBDS_KBD_BUFFER_FULL) {
		addq(&kbdc->kbd, b);
	    }
	}
        DELAY(KBDC_DELAYTIME);
    }
    return -1;
}