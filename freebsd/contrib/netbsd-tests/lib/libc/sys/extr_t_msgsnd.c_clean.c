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
 int /*<<< orphan*/  IPC_RMID ; 
 int /*<<< orphan*/  MSG_KEY ; 
 int /*<<< orphan*/  msgctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int msgget (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
clean(void)
{
	int id;

	if ((id = msgget(MSG_KEY, 0)) != -1)
		(void)msgctl(id, IPC_RMID, 0);
}