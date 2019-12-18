#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  void* dtrace_id_t ;
struct TYPE_2__ {void* sy_return; void* sy_entry; int /*<<< orphan*/ * sy_systrace_args_func; } ;

/* Variables and functions */
 TYPE_1__* SYSENT ; 
 scalar_t__ SYSTRACE_ISENTRY (uintptr_t) ; 
 int SYSTRACE_SYSNUM (uintptr_t) ; 
 int /*<<< orphan*/ * systrace_args ; 
 int systrace_enabled ; 
 int systrace_enabled_count ; 

__attribute__((used)) static void
systrace_enable(void *arg, dtrace_id_t id, void *parg)
{
	int sysnum = SYSTRACE_SYSNUM((uintptr_t)parg);

	if (SYSENT[sysnum].sy_systrace_args_func == NULL)
		SYSENT[sysnum].sy_systrace_args_func = systrace_args;

	if (SYSTRACE_ISENTRY((uintptr_t)parg))
		SYSENT[sysnum].sy_entry = id;
	else
		SYSENT[sysnum].sy_return = id;
	systrace_enabled_count++;
	if (systrace_enabled_count == 1)
		systrace_enabled = true;
}