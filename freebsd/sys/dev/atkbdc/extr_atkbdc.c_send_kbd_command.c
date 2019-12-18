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
typedef  int /*<<< orphan*/  KBDC ;

/* Variables and functions */
 int KBD_ACK ; 
 int KBD_MAXRETRY ; 
 int /*<<< orphan*/  kbdcp (int /*<<< orphan*/ ) ; 
 int wait_for_kbd_ack (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_kbd_command (int /*<<< orphan*/ ,int) ; 

int
send_kbd_command(KBDC p, int c)
{
    int retry = KBD_MAXRETRY;
    int res = -1;

    while (retry-- > 0) {
	if (!write_kbd_command(p, c))
	    continue;
        res = wait_for_kbd_ack(kbdcp(p));
        if (res == KBD_ACK)
    	    break;
    }
    return res;
}