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
struct atkbdc_softc {int retry; int /*<<< orphan*/  aux; int /*<<< orphan*/  kbd; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int /*<<< orphan*/ ) ; 
 int FALSE ; 
 int /*<<< orphan*/  KBDC_DELAYTIME ; 
 int /*<<< orphan*/  KBDD_DELAYTIME ; 
 int KBDS_AUX_BUFFER_FULL ; 
 int KBDS_BUFFER_FULL ; 
 int KBDS_INPUT_BUFFER_FULL ; 
 int KBDS_KBD_BUFFER_FULL ; 
 int TRUE ; 
 int /*<<< orphan*/  addq (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_data (struct atkbdc_softc*) ; 
 int read_status (struct atkbdc_softc*) ; 

__attribute__((used)) static int
wait_while_controller_busy(struct atkbdc_softc *kbdc)
{
    int retry;
    int f;

    /* CPU will stay inside the loop for 100msec at most */
    retry = kbdc->retry;

    while ((f = read_status(kbdc)) & KBDS_INPUT_BUFFER_FULL) {
	if ((f & KBDS_BUFFER_FULL) == KBDS_KBD_BUFFER_FULL) {
	    DELAY(KBDD_DELAYTIME);
	    addq(&kbdc->kbd, read_data(kbdc));
	} else if ((f & KBDS_BUFFER_FULL) == KBDS_AUX_BUFFER_FULL) {
	    DELAY(KBDD_DELAYTIME);
	    addq(&kbdc->aux, read_data(kbdc));
	}
        DELAY(KBDC_DELAYTIME);
        if (--retry < 0)
    	    return FALSE;
    }
    return TRUE;
}