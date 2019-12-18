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
 int /*<<< orphan*/  LOG_CRITICAL ; 
 int /*<<< orphan*/  LOG_DEF ; 
 int /*<<< orphan*/  LOG_HISTORY ; 
 int /*<<< orphan*/  LOG_WARNINGS ; 
 int /*<<< orphan*/  SIGABRT ; 
 int /*<<< orphan*/  SIGSEGV ; 
 int /*<<< orphan*/  dl_log_set_verb (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  dl_runtime_handler ; 
 int /*<<< orphan*/  dl_signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void dl_set_debug_handlers (void) {
//  signal (SIGFPE, dl_runtime_handler);
  dl_signal (SIGSEGV, dl_runtime_handler);
  dl_signal (SIGABRT, dl_runtime_handler);

  //TODO: move this somewhere else
#ifdef DL_DEBUG_OUT
  dl_log_set_verb (LOG_DEF, 3, 3);
#else
  dl_log_set_verb (LOG_DEF, 0, 3);
#endif
  dl_log_set_verb (LOG_HISTORY, 0, 0x7F);
  dl_log_set_verb (LOG_WARNINGS, 0, 9);
  dl_log_set_verb (LOG_CRITICAL, 0, 9);
}