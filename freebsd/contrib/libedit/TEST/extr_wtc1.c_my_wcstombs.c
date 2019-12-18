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
typedef  int /*<<< orphan*/  wchar_t ;

/* Variables and functions */
 char* malloc (int) ; 
 int /*<<< orphan*/  wcstombs (char*,int /*<<< orphan*/  const*,int) ; 

const char *
my_wcstombs(const wchar_t *wstr)
{
	static struct {
		char *str;
		int len;
	} buf;

	int needed = wcstombs(0, wstr, 0) + 1;
	if (needed > buf.len) {
		buf.str = malloc(needed);
		buf.len = needed;
	}
	wcstombs(buf.str, wstr, needed);
	buf.str[needed - 1] = 0;

	return buf.str;
}