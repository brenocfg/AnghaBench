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
struct TYPE_3__ {scalar_t__ wAttributes; } ;
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  TYPE_1__ CONSOLE_SCREEN_BUFFER_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  FD_CONSOLE ; 
 scalar_t__ FILE_TYPE_CHAR ; 
 int /*<<< orphan*/  GetConsoleMode (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetConsoleScreenBufferInfo (scalar_t__,TYPE_1__*) ; 
 scalar_t__ GetFileType (scalar_t__) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 scalar_t__ _get_osfhandle (int) ; 
 scalar_t__ attr ; 
 scalar_t__ console ; 
 int /*<<< orphan*/ * fd_is_interactive ; 
 scalar_t__ negative ; 
 scalar_t__ plain_attr ; 

__attribute__((used)) static int is_console(int fd)
{
	CONSOLE_SCREEN_BUFFER_INFO sbi;
	DWORD mode;
	HANDLE hcon;

	static int initialized = 0;

	/* get OS handle of the file descriptor */
	hcon = (HANDLE) _get_osfhandle(fd);
	if (hcon == INVALID_HANDLE_VALUE)
		return 0;

	/* check if its a device (i.e. console, printer, serial port) */
	if (GetFileType(hcon) != FILE_TYPE_CHAR)
		return 0;

	/* check if its a handle to a console output screen buffer */
	if (!fd) {
		if (!GetConsoleMode(hcon, &mode))
			return 0;
		/*
		 * This code path is only reached if there is no console
		 * attached to stdout/stderr, i.e. we will not need to output
		 * any text to any console, therefore we might just as well
		 * use black as foreground color.
		 */
		sbi.wAttributes = 0;
	} else if (!GetConsoleScreenBufferInfo(hcon, &sbi))
		return 0;

	if (fd >= 0 && fd <= 2)
		fd_is_interactive[fd] |= FD_CONSOLE;

	/* initialize attributes */
	if (!initialized) {
		console = hcon;
		attr = plain_attr = sbi.wAttributes;
		negative = 0;
		initialized = 1;
	}

	return 1;
}