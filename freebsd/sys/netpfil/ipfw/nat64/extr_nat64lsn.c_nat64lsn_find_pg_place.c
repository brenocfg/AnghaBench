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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int ffs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nat64lsn_find_pg_place(uint32_t *data)
{
	int i;

	for (i = 0; i < 32; i++) {
		if (~data[i] == 0)
			continue;
		return (i * 32 + ffs(~data[i]) - 1);
	}
	return (-1);
}