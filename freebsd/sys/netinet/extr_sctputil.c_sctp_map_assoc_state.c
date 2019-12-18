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
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SCTP_CLOSED ; 
 int /*<<< orphan*/  SCTP_COOKIE_ECHOED ; 
 int /*<<< orphan*/  SCTP_COOKIE_WAIT ; 
 int /*<<< orphan*/  SCTP_ESTABLISHED ; 
 int /*<<< orphan*/  SCTP_SHUTDOWN_ACK_SENT ; 
 int /*<<< orphan*/  SCTP_SHUTDOWN_PENDING ; 
 int /*<<< orphan*/  SCTP_SHUTDOWN_RECEIVED ; 
 int /*<<< orphan*/  SCTP_SHUTDOWN_SENT ; 
#define  SCTP_STATE_COOKIE_ECHOED 135 
#define  SCTP_STATE_COOKIE_WAIT 134 
#define  SCTP_STATE_EMPTY 133 
#define  SCTP_STATE_INUSE 132 
 int SCTP_STATE_MASK ; 
#define  SCTP_STATE_OPEN 131 
#define  SCTP_STATE_SHUTDOWN_ACK_SENT 130 
 int SCTP_STATE_SHUTDOWN_PENDING ; 
#define  SCTP_STATE_SHUTDOWN_RECEIVED 129 
#define  SCTP_STATE_SHUTDOWN_SENT 128 
 int SCTP_STATE_WAS_ABORTED ; 

int32_t
sctp_map_assoc_state(int kernel_state)
{
	int32_t user_state;

	if (kernel_state & SCTP_STATE_WAS_ABORTED) {
		user_state = SCTP_CLOSED;
	} else if (kernel_state & SCTP_STATE_SHUTDOWN_PENDING) {
		user_state = SCTP_SHUTDOWN_PENDING;
	} else {
		switch (kernel_state & SCTP_STATE_MASK) {
		case SCTP_STATE_EMPTY:
			user_state = SCTP_CLOSED;
			break;
		case SCTP_STATE_INUSE:
			user_state = SCTP_CLOSED;
			break;
		case SCTP_STATE_COOKIE_WAIT:
			user_state = SCTP_COOKIE_WAIT;
			break;
		case SCTP_STATE_COOKIE_ECHOED:
			user_state = SCTP_COOKIE_ECHOED;
			break;
		case SCTP_STATE_OPEN:
			user_state = SCTP_ESTABLISHED;
			break;
		case SCTP_STATE_SHUTDOWN_SENT:
			user_state = SCTP_SHUTDOWN_SENT;
			break;
		case SCTP_STATE_SHUTDOWN_RECEIVED:
			user_state = SCTP_SHUTDOWN_RECEIVED;
			break;
		case SCTP_STATE_SHUTDOWN_ACK_SENT:
			user_state = SCTP_SHUTDOWN_ACK_SENT;
			break;
		default:
			user_state = SCTP_CLOSED;
			break;
		}
	}
	return (user_state);
}