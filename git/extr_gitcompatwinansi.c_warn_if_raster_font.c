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
typedef  char wchar_t ;
typedef  int /*<<< orphan*/  fontFamily ;
typedef  int /*<<< orphan*/  cfi ;
struct TYPE_3__ {int cbSize; int FontFamily; } ;
typedef  scalar_t__ (* PGETCURRENTCONSOLEFONTEX ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;
typedef  TYPE_1__ CONSOLE_FONT_INFOEX ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  GetModuleHandle (char*) ; 
 scalar_t__ GetProcAddress (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int /*<<< orphan*/  KEY_READ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegOpenKeyExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegQueryValueExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int TMPF_TRUETYPE ; 
 int /*<<< orphan*/  WriteConsoleW (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  console ; 
 int /*<<< orphan*/  non_ascii_used ; 
 int /*<<< orphan*/  wcslen (char const*) ; 

__attribute__((used)) static void warn_if_raster_font(void)
{
	DWORD fontFamily = 0;
	PGETCURRENTCONSOLEFONTEX pGetCurrentConsoleFontEx;

	/* don't bother if output was ascii only */
	if (!non_ascii_used)
		return;

	/* GetCurrentConsoleFontEx is available since Vista */
	pGetCurrentConsoleFontEx = (PGETCURRENTCONSOLEFONTEX) GetProcAddress(
			GetModuleHandle("kernel32.dll"),
			"GetCurrentConsoleFontEx");
	if (pGetCurrentConsoleFontEx) {
		CONSOLE_FONT_INFOEX cfi;
		cfi.cbSize = sizeof(cfi);
		if (pGetCurrentConsoleFontEx(console, 0, &cfi))
			fontFamily = cfi.FontFamily;
	} else {
		/* pre-Vista: check default console font in registry */
		HKEY hkey;
		if (ERROR_SUCCESS == RegOpenKeyExA(HKEY_CURRENT_USER, "Console",
				0, KEY_READ, &hkey)) {
			DWORD size = sizeof(fontFamily);
			RegQueryValueExA(hkey, "FontFamily", NULL, NULL,
					(LPVOID) &fontFamily, &size);
			RegCloseKey(hkey);
		}
	}

	if (!(fontFamily & TMPF_TRUETYPE)) {
		const wchar_t *msg = L"\nWarning: Your console font probably "
			L"doesn\'t support Unicode. If you experience strange "
			L"characters in the output, consider switching to a "
			L"TrueType font such as Consolas!\n";
		DWORD dummy;
		WriteConsoleW(console, msg, wcslen(msg), &dummy, NULL);
	}
}