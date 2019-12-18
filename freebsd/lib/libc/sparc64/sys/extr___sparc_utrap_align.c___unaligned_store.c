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
typedef  int u_long ;
typedef  int u_char ;

/* Variables and functions */

__attribute__((used)) static void
__unaligned_store(u_char *p, u_long val, int size)
{
	int i;

	for (i = 0; i < size; i++)
		p[i] = val >> ((size - i - 1) * 8);
}