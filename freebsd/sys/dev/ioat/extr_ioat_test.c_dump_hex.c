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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
dump_hex(void *p, size_t chunks)
{
	size_t i, j;

	for (i = 0; i < chunks; i++) {
		for (j = 0; j < 8; j++)
			printf("%08x ", ((uint32_t *)p)[i * 8 + j]);
		printf("\n");
	}
}