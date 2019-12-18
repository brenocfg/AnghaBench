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
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;
struct opal_msg {int /*<<< orphan*/  msg_type; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  EVENTHANDLER_DIRECT_INVOKE (int /*<<< orphan*/ ,struct opal_msg*) ; 
 int /*<<< orphan*/  OPAL_ASYNC_COMP ; 
 int /*<<< orphan*/  OPAL_DPO ; 
 int /*<<< orphan*/  OPAL_EPOW ; 
 int /*<<< orphan*/  OPAL_GET_MSG ; 
 int /*<<< orphan*/  OPAL_HMI_EVT ; 
#define  OPAL_MSG_ASYNC_COMP 133 
#define  OPAL_MSG_DPO 132 
#define  OPAL_MSG_EPOW 131 
#define  OPAL_MSG_HMI_EVT 130 
#define  OPAL_MSG_OCC 129 
#define  OPAL_MSG_SHUTDOWN 128 
 int /*<<< orphan*/  OPAL_OCC ; 
 int /*<<< orphan*/  OPAL_SHUTDOWN ; 
 scalar_t__ OPAL_SUCCESS ; 
 int be32toh (int /*<<< orphan*/ ) ; 
 scalar_t__ opal_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  vtophys (struct opal_msg*) ; 

__attribute__((used)) static void
opal_handle_messages(void)
{
	static struct opal_msg msg;
	uint64_t rv;
	uint32_t type;

	rv = opal_call(OPAL_GET_MSG, vtophys(&msg), sizeof(msg));
	
	if (rv != OPAL_SUCCESS)
		return;

	type = be32toh(msg.msg_type);
	switch (type) {
	case OPAL_MSG_ASYNC_COMP:
		EVENTHANDLER_DIRECT_INVOKE(OPAL_ASYNC_COMP, &msg);
		break;
	case OPAL_MSG_EPOW:
		EVENTHANDLER_DIRECT_INVOKE(OPAL_EPOW, &msg);
		break;
	case OPAL_MSG_SHUTDOWN:
		EVENTHANDLER_DIRECT_INVOKE(OPAL_SHUTDOWN, &msg);
		break;
	case OPAL_MSG_HMI_EVT:
		EVENTHANDLER_DIRECT_INVOKE(OPAL_HMI_EVT, &msg);
		break;
	case OPAL_MSG_DPO:
		EVENTHANDLER_DIRECT_INVOKE(OPAL_DPO, &msg);
		break;
	case OPAL_MSG_OCC:
		EVENTHANDLER_DIRECT_INVOKE(OPAL_OCC, &msg);
		break;
	default:
		printf("Unknown OPAL message type %d\n", type);
	}
}