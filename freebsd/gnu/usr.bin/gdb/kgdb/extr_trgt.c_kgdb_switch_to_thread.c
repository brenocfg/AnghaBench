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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  gdb_thread_select (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pid_to_ptid (int) ; 
 int pid_to_thread_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  uiout ; 

__attribute__((used)) static void
kgdb_switch_to_thread(int tid)
{
	char buf[16];
	int thread_id;

	thread_id = pid_to_thread_id(pid_to_ptid(tid));
	if (thread_id == 0)
		error ("invalid tid");
	snprintf(buf, sizeof(buf), "%d", thread_id);
	gdb_thread_select(uiout, buf);
}