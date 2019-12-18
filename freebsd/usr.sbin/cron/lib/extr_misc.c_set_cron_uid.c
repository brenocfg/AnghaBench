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
 int /*<<< orphan*/  ERROR_EXIT ; 
 scalar_t__ OK ; 
 int /*<<< orphan*/  ROOT_UID ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ seteuid (int /*<<< orphan*/ ) ; 
 scalar_t__ setuid (int /*<<< orphan*/ ) ; 

void
set_cron_uid()
{
#if defined(BSD) || defined(POSIX)
	if (seteuid(ROOT_UID) < OK)
		err(ERROR_EXIT, "seteuid");
#else
	if (setuid(ROOT_UID) < OK)
		err(ERROR_EXIT, "setuid");
#endif
}