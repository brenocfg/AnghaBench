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

/* Variables and functions */

__attribute__((used)) static void
append_id(char **p, int id)
{
	if (id < 0)
		id = 0;
	if (id > 9)
		append_id(p, id / 10);
	*(*p)++ = "0123456789"[id % 10];
}