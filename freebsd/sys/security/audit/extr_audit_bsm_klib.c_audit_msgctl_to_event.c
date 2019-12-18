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
typedef  int /*<<< orphan*/  au_event_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUE_MSGCTL ; 
 int /*<<< orphan*/  AUE_MSGCTL_RMID ; 
 int /*<<< orphan*/  AUE_MSGCTL_SET ; 
 int /*<<< orphan*/  AUE_MSGCTL_STAT ; 
#define  IPC_RMID 130 
#define  IPC_SET 129 
#define  IPC_STAT 128 

au_event_t
audit_msgctl_to_event(int cmd)
{

	switch (cmd) {
	case IPC_RMID:
		return (AUE_MSGCTL_RMID);

	case IPC_SET:
		return (AUE_MSGCTL_SET);

	case IPC_STAT:
		return (AUE_MSGCTL_STAT);

	default:
		/* We will audit a bad command. */
		return (AUE_MSGCTL);
	}
}