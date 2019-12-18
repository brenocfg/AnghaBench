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

/* Variables and functions */
 void* IAC ; 
 int NETROOM () ; 
 int /*<<< orphan*/  SB ; 
 int /*<<< orphan*/  SE ; 
 int /*<<< orphan*/  TELOPT_STATUS ; 
 int /*<<< orphan*/  TELQUAL_SEND ; 
 scalar_t__ my_want_state_is_dont (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netoring ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  printsub (char,unsigned char*,int) ; 
 int /*<<< orphan*/  ring_supply_data (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  want_status_response ; 

int
get_status()
{
    unsigned char tmp[16];
    unsigned char *cp;

    if (my_want_state_is_dont(TELOPT_STATUS)) {
	printf("Remote side does not support STATUS option\n");
	return 0;
    }
    cp = tmp;

    *cp++ = IAC;
    *cp++ = SB;
    *cp++ = TELOPT_STATUS;
    *cp++ = TELQUAL_SEND;
    *cp++ = IAC;
    *cp++ = SE;
    if (NETROOM() >= cp - tmp) {
	ring_supply_data(&netoring, tmp, cp-tmp);
	printsub('>', tmp+2, cp - tmp - 2);
    }
    ++want_status_response;
    return 1;
}