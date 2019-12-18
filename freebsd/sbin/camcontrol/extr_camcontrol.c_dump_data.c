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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int u_int ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
dump_data(uint16_t *ptr, uint32_t len)
{
	u_int i;

	for (i = 0; i < len / 2; i++) {
		if ((i % 8) == 0)
			printf(" %3d: ", i);
		printf("%04hx ", ptr[i]);
		if ((i % 8) == 7)
			printf("\n");
	}
	if ((i % 8) != 7)
		printf("\n");
}