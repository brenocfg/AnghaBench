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
typedef  int /*<<< orphan*/  WCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  CP_UTF8 ; 
 int MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * xmalloc (int) ; 

__attribute__((used)) static WCHAR *utf8_to_utf16_dup(const char *str)
{
	int wlen = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
	WCHAR *wstr = xmalloc(sizeof(WCHAR) * wlen);
	MultiByteToWideChar(CP_UTF8, 0, str, -1, wstr, wlen);
	return wstr;
}