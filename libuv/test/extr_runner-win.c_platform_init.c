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
 int /*<<< orphan*/  _CRTDBG_MODE_DEBUG ; 
 int /*<<< orphan*/  _CRT_ASSERT ; 
 int /*<<< orphan*/  _CRT_ERROR ; 
 int /*<<< orphan*/  _CrtSetReportMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _IONBF ; 
 int /*<<< orphan*/  _O_BINARY ; 
 int /*<<< orphan*/  _fmode ; 
 int /*<<< orphan*/  _set_fmode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _setmode (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  executable_path ; 
 int /*<<< orphan*/  setvbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

int platform_init(int argc, char **argv) {
  /* Disable the "application crashed" popup. */
  SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX |
      SEM_NOOPENFILEERRORBOX);
#if !defined(__MINGW32__)
  _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_DEBUG);
  _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
#endif

  _setmode(0, _O_BINARY);
  _setmode(1, _O_BINARY);
  _setmode(2, _O_BINARY);

#ifdef _MSC_VER
  _set_fmode(_O_BINARY);
#else
  _fmode = _O_BINARY;
#endif

  /* Disable stdio output buffering. */
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

  strcpy(executable_path, argv[0]);

  return 0;
}