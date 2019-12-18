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
#define  LM_FORWARDMASK 128 
 int /*<<< orphan*/  printf (char*) ; 

void
lm_dont(unsigned char *cmd, int len)
{
    if (len < 1) {
/*@*/	printf("lm_dont: no command!!!\n");	/* Should not happen... */
	return;
    }
    switch(cmd[0]) {
    case LM_FORWARDMASK:
    default:
	/* we are always WONT, so don't respond */
	break;
    }
}