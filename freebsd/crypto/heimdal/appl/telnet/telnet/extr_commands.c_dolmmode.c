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
 int /*<<< orphan*/  TELOPT_LINEMODE ; 
 int linemode ; 
 int /*<<< orphan*/  lm_mode (unsigned char*,int,int) ; 
 scalar_t__ my_want_state_is_wont (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int
dolmmode(int bit, int on)
{
    unsigned char c;

    if (my_want_state_is_wont(TELOPT_LINEMODE)) {
	printf("?Need to have LINEMODE option enabled first.\r\n");
	printf("'mode ?' for help.\r\n");
 	return 0;
    }

    if (on)
	c = (linemode | bit);
    else
	c = (linemode & ~bit);
    lm_mode(&c, 1, 1);
    return 1;
}