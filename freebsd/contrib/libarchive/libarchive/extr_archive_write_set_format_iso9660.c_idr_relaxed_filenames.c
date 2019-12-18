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
idr_relaxed_filenames(char *map)
{
	int i;

	for (i = 0x21; i <= 0x2F; i++)
		map[i] = 1;
	for (i = 0x3A; i <= 0x41; i++)
		map[i] = 1;
	for (i = 0x5B; i <= 0x5E; i++)
		map[i] = 1;
	map[0x60] = 1;
	for (i = 0x7B; i <= 0x7E; i++)
		map[i] = 1;
}