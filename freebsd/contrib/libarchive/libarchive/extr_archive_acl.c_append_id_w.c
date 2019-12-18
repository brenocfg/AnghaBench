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

__attribute__((used)) static void
append_id_w(wchar_t **wp, int id)
{
	if (id < 0)
		id = 0;
	if (id > 9)
		append_id_w(wp, id / 10);
	*(*wp)++ = L"0123456789"[id % 10];
}