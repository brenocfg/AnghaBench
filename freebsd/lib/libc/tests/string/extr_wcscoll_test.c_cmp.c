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
 int wcscoll (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int
cmp(const void *a, const void *b)
{
	const wchar_t wa[2] = { *(const wchar_t *)a, 0 };
	const wchar_t wb[2] = { *(const wchar_t *)b, 0 };

	return (wcscoll(wa, wb));
}