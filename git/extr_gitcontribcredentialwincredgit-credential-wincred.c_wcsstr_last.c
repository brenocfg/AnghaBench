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
typedef  int /*<<< orphan*/ * LPCWSTR ;

/* Variables and functions */
 int /*<<< orphan*/ * wcsstr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static LPCWSTR wcsstr_last(LPCWSTR str, LPCWSTR find)
{
	LPCWSTR res = NULL, pos;
	for (pos = wcsstr(str, find); pos; pos = wcsstr(pos + 1, find))
		res = pos;
	return res;
}