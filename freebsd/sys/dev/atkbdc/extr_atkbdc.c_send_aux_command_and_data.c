#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  aux; } ;
typedef  int /*<<< orphan*/  KBDC ;

/* Variables and functions */
 int KBD_MAXRETRY ; 
 int PSM_ACK ; 
 int PSM_RESEND ; 
 int /*<<< orphan*/  emptyq (int /*<<< orphan*/ *) ; 
 TYPE_1__* kbdcp (int /*<<< orphan*/ ) ; 
 int wait_for_aux_ack (TYPE_1__*) ; 
 int /*<<< orphan*/  write_aux_command (int /*<<< orphan*/ ,int) ; 

int
send_aux_command_and_data(KBDC p, int c, int d)
{
    int retry;
    int res = -1;

    for (retry = KBD_MAXRETRY; retry > 0; --retry) {
	if (!write_aux_command(p, c))
	    continue;
	emptyq(&kbdcp(p)->aux);
        res = wait_for_aux_ack(kbdcp(p));
        if (res == PSM_ACK)
    	    break;
        else if (res != PSM_RESEND)
    	    return res;
    }
    if (retry <= 0)
	return res;

    for (retry = KBD_MAXRETRY, res = -1; retry > 0; --retry) {
	if (!write_aux_command(p, d))
	    continue;
        res = wait_for_aux_ack(kbdcp(p));
        if (res != PSM_RESEND)
    	    break;
    }
    return res;
}