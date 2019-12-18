#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  xxfi_name; } ;

/* Variables and functions */
 int MI_FAILURE ; 
 int MI_MONITOR_INIT () ; 
 scalar_t__ MI_SUCCESS ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  SMI_LOG_FATAL ; 
 int /*<<< orphan*/  atexit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  backlog ; 
 int /*<<< orphan*/ * conn ; 
 int /*<<< orphan*/  dbg ; 
 int /*<<< orphan*/  mi_clean_signals ; 
 scalar_t__ mi_control_startup (int /*<<< orphan*/ ) ; 
 scalar_t__ mi_listener (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* smfi ; 
 int /*<<< orphan*/  smi_log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timeout ; 

int
smfi_main()
{
	int r;

	(void) signal(SIGPIPE, SIG_IGN);
	if (conn == NULL)
	{
		smi_log(SMI_LOG_FATAL, "%s: missing connection information",
			smfi->xxfi_name);
		return MI_FAILURE;
	}

	(void) atexit(mi_clean_signals);
	if (mi_control_startup(smfi->xxfi_name) != MI_SUCCESS)
	{
		smi_log(SMI_LOG_FATAL,
			"%s: Couldn't start signal thread",
			smfi->xxfi_name);
		return MI_FAILURE;
	}
	r = MI_MONITOR_INIT();

	/* Startup the listener */
	if (mi_listener(conn, dbg, smfi, timeout, backlog) != MI_SUCCESS)
		r = MI_FAILURE;

	return r;
}