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
typedef  int u_int8_t ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
dumpdata(const char *tag, const void *p, size_t len)
{
	int i;

	printf("%s: 0x%p len %u", tag, p, len);
	for (i = 0; i < len; i++) {
		if ((i % 16) == 0)
			printf("\n%03d:", i);
		printf(" %02x", ((const u_int8_t *)p)[i]);
	}
	printf("\n");
}