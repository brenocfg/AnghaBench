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
 int entries ; 
 int /*<<< orphan*/ ** list ; 
 int /*<<< orphan*/  wprintf (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
print(void)
{
	int cnt;
	wchar_t **lp;

	for (cnt = entries, lp = list; cnt--; ++lp)
		(void)wprintf(L"%ls\n", *lp);
}