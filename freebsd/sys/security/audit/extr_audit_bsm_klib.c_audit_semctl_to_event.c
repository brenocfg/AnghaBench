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
 int /*<<< orphan*/  AUE_SEMCTL ; 
 int /*<<< orphan*/  AUE_SEMCTL_GETALL ; 
 int /*<<< orphan*/  AUE_SEMCTL_GETNCNT ; 
 int /*<<< orphan*/  AUE_SEMCTL_GETPID ; 
 int /*<<< orphan*/  AUE_SEMCTL_GETVAL ; 
 int /*<<< orphan*/  AUE_SEMCTL_GETZCNT ; 
 int /*<<< orphan*/  AUE_SEMCTL_RMID ; 
 int /*<<< orphan*/  AUE_SEMCTL_SET ; 
 int /*<<< orphan*/  AUE_SEMCTL_SETALL ; 
 int /*<<< orphan*/  AUE_SEMCTL_SETVAL ; 
 int /*<<< orphan*/  AUE_SEMCTL_STAT ; 
#define  GETALL 137 
#define  GETNCNT 136 
#define  GETPID 135 
#define  GETVAL 134 
#define  GETZCNT 133 
#define  IPC_RMID 132 
#define  IPC_SET 131 
#define  IPC_STAT 130 
#define  SETALL 129 
#define  SETVAL 128 

au_event_t
audit_semctl_to_event(int cmd)
{

	switch (cmd) {
	case GETALL:
		return (AUE_SEMCTL_GETALL);

	case GETNCNT:
		return (AUE_SEMCTL_GETNCNT);

	case GETPID:
		return (AUE_SEMCTL_GETPID);

	case GETVAL:
		return (AUE_SEMCTL_GETVAL);

	case GETZCNT:
		return (AUE_SEMCTL_GETZCNT);

	case IPC_RMID:
		return (AUE_SEMCTL_RMID);

	case IPC_SET:
		return (AUE_SEMCTL_SET);

	case SETALL:
		return (AUE_SEMCTL_SETALL);

	case SETVAL:
		return (AUE_SEMCTL_SETVAL);

	case IPC_STAT:
		return (AUE_SEMCTL_STAT);

	default:
		/* We will audit a bad command. */
		return (AUE_SEMCTL);
	}
}