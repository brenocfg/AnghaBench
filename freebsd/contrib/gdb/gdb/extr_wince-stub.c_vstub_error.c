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
typedef  int /*<<< orphan*/  va_list ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  LPCWSTR ;

/* Variables and functions */
 int /*<<< orphan*/  ExitThread (int) ; 
 int /*<<< orphan*/  MB_ICONERROR ; 
 int /*<<< orphan*/  MessageBoxW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WSACleanup () ; 
 int /*<<< orphan*/  wvsprintfW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vstub_error (LPCWSTR fmt, va_list args)
{
  WCHAR buf[4096];
  wvsprintfW (buf, fmt, args);

  MessageBoxW (NULL, buf, L"GDB", MB_ICONERROR);
  WSACleanup ();
  ExitThread (1);
}