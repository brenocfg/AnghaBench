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
#define  SCTP_BOUND 137 
#define  SCTP_CLOSED 136 
#define  SCTP_COOKIE_ECHOED 135 
#define  SCTP_COOKIE_WAIT 134 
#define  SCTP_ESTABLISHED 133 
#define  SCTP_LISTEN 132 
#define  SCTP_SHUTDOWN_ACK_SENT 131 
#define  SCTP_SHUTDOWN_PENDING 130 
#define  SCTP_SHUTDOWN_RECEIVED 129 
#define  SCTP_SHUTDOWN_SENT 128 

__attribute__((used)) static const char *
sctp_conn_state(int state)
{
	switch (state) {
	case SCTP_CLOSED:
		return "CLOSED";
		break;
	case SCTP_BOUND:
		return "BOUND";
		break;
	case SCTP_LISTEN:
		return "LISTEN";
		break;
	case SCTP_COOKIE_WAIT:
		return "COOKIE_WAIT";
		break;
	case SCTP_COOKIE_ECHOED:
		return "COOKIE_ECHOED";
		break;
	case SCTP_ESTABLISHED:
		return "ESTABLISHED";
		break;
	case SCTP_SHUTDOWN_SENT:
		return "SHUTDOWN_SENT";
		break;
	case SCTP_SHUTDOWN_RECEIVED:
		return "SHUTDOWN_RECEIVED";
		break;
	case SCTP_SHUTDOWN_ACK_SENT:
		return "SHUTDOWN_ACK_SENT";
		break;
	case SCTP_SHUTDOWN_PENDING:
		return "SHUTDOWN_PENDING";
		break;
	default:
		return "UNKNOWN";
		break;
	}
}