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
#define  BT_STATE_CLEAR_B2H 139 
#define  BT_STATE_IDLE 138 
#define  BT_STATE_LONG_BUSY 137 
#define  BT_STATE_READ_BYTES 136 
#define  BT_STATE_READ_WAIT 135 
#define  BT_STATE_RESET1 134 
#define  BT_STATE_RESET2 133 
#define  BT_STATE_RESET3 132 
#define  BT_STATE_RESTART 131 
#define  BT_STATE_WRITE_BYTES 130 
#define  BT_STATE_WRITE_CONSUME 129 
#define  BT_STATE_XACTION_START 128 

__attribute__((used)) static char *state2txt(unsigned char state)
{
	switch (state) {
	case BT_STATE_IDLE:		return("IDLE");
	case BT_STATE_XACTION_START:	return("XACTION");
	case BT_STATE_WRITE_BYTES:	return("WR_BYTES");
	case BT_STATE_WRITE_CONSUME:	return("WR_CONSUME");
	case BT_STATE_READ_WAIT:	return("RD_WAIT");
	case BT_STATE_CLEAR_B2H:	return("CLEAR_B2H");
	case BT_STATE_READ_BYTES:	return("RD_BYTES");
	case BT_STATE_RESET1:		return("RESET1");
	case BT_STATE_RESET2:		return("RESET2");
	case BT_STATE_RESET3:		return("RESET3");
	case BT_STATE_RESTART:		return("RESTART");
	case BT_STATE_LONG_BUSY:	return("LONG_BUSY");
	}
	return("BAD STATE");
}