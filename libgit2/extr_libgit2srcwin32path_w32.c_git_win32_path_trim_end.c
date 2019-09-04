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
typedef  int wchar_t ;

/* Variables and functions */
 scalar_t__ git_win32__isalpha (int) ; 

size_t git_win32_path_trim_end(wchar_t *str, size_t len)
{
	while (1) {
		if (!len || str[len - 1] != L'\\')
			break;

		/*
		 * Don't trim backslashes from drive letter paths, which
		 * are 3 characters long and of the form C:\, D:\, etc.
		 */
		if (len == 3 && git_win32__isalpha(str[0]) && str[1] == ':')
			break;

		len--;
	}

	str[len] = L'\0';

	return len;
}