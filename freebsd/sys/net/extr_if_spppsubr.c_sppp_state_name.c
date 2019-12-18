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
#define  STATE_ACK_RCVD 137 
#define  STATE_ACK_SENT 136 
#define  STATE_CLOSED 135 
#define  STATE_CLOSING 134 
#define  STATE_INITIAL 133 
#define  STATE_OPENED 132 
#define  STATE_REQ_SENT 131 
#define  STATE_STARTING 130 
#define  STATE_STOPPED 129 
#define  STATE_STOPPING 128 

__attribute__((used)) static const char *
sppp_state_name(int state)
{
	switch (state) {
	case STATE_INITIAL:	return "initial";
	case STATE_STARTING:	return "starting";
	case STATE_CLOSED:	return "closed";
	case STATE_STOPPED:	return "stopped";
	case STATE_CLOSING:	return "closing";
	case STATE_STOPPING:	return "stopping";
	case STATE_REQ_SENT:	return "req-sent";
	case STATE_ACK_RCVD:	return "ack-rcvd";
	case STATE_ACK_SENT:	return "ack-sent";
	case STATE_OPENED:	return "opened";
	}
	return "illegal";
}