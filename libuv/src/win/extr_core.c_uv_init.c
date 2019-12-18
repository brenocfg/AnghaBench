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
 int SEM_FAILCRITICALERRORS ; 
 int SEM_NOGPFAULTERRORBOX ; 
 int SEM_NOOPENFILEERRORBOX ; 
 int /*<<< orphan*/  SetErrorMode (int) ; 
 int /*<<< orphan*/  _CrtSetReportHook (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _set_invalid_parameter_handler (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv__crt_dbg_report_handler ; 
 int /*<<< orphan*/  uv__crt_invalid_parameter_handler ; 
 int /*<<< orphan*/  uv__init_detect_system_wakeup () ; 
 int /*<<< orphan*/  uv__loops_init () ; 
 int /*<<< orphan*/  uv__util_init () ; 
 int /*<<< orphan*/  uv_console_init () ; 
 int /*<<< orphan*/  uv_fs_init () ; 
 int /*<<< orphan*/  uv_signals_init () ; 
 int /*<<< orphan*/  uv_winapi_init () ; 
 int /*<<< orphan*/  uv_winsock_init () ; 

__attribute__((used)) static void uv_init(void) {
  /* Tell Windows that we will handle critical errors. */
  SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX |
               SEM_NOOPENFILEERRORBOX);

  /* Tell the CRT to not exit the application when an invalid parameter is
   * passed. The main issue is that invalid FDs will trigger this behavior.
   */
#if !defined(__MINGW32__) || __MSVCRT_VERSION__ >= 0x800
  _set_invalid_parameter_handler(uv__crt_invalid_parameter_handler);
#endif

  /* We also need to setup our debug report handler because some CRT
   * functions (eg _get_osfhandle) raise an assert when called with invalid
   * FDs even though they return the proper error code in the release build.
   */
#if defined(_DEBUG) && (defined(_MSC_VER) || defined(__MINGW64_VERSION_MAJOR))
  _CrtSetReportHook(uv__crt_dbg_report_handler);
#endif

  /* Initialize tracking of all uv loops */
  uv__loops_init();

  /* Fetch winapi function pointers. This must be done first because other
   * initialization code might need these function pointers to be loaded.
   */
  uv_winapi_init();

  /* Initialize winsock */
  uv_winsock_init();

  /* Initialize FS */
  uv_fs_init();

  /* Initialize signal stuff */
  uv_signals_init();

  /* Initialize console */
  uv_console_init();

  /* Initialize utilities */
  uv__util_init();

  /* Initialize system wakeup detection */
  uv__init_detect_system_wakeup();
}