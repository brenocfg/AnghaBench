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
typedef  char wchar_t ;

/* Variables and functions */
 int /*<<< orphan*/  wcsncmp (char*,char*,int) ; 
 int /*<<< orphan*/  wcsnicmp (char*,char*,int) ; 

__attribute__((used)) static wchar_t *normalize_ntpath(wchar_t *wbuf)
{
	int i;
	/* fix absolute path prefixes */
	if (wbuf[0] == '\\') {
		/* strip NT namespace prefixes */
		if (!wcsncmp(wbuf, L"\\??\\", 4) ||
		    !wcsncmp(wbuf, L"\\\\?\\", 4))
			wbuf += 4;
		else if (!wcsnicmp(wbuf, L"\\DosDevices\\", 12))
			wbuf += 12;
		/* replace remaining '...UNC\' with '\\' */
		if (!wcsnicmp(wbuf, L"UNC\\", 4)) {
			wbuf += 2;
			*wbuf = '\\';
		}
	}
	/* convert backslashes to slashes */
	for (i = 0; wbuf[i]; i++)
		if (wbuf[i] == '\\')
			wbuf[i] = '/';
	return wbuf;
}