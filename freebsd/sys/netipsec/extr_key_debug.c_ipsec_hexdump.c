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
typedef  scalar_t__* caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 

void
ipsec_hexdump(caddr_t buf, int len)
{
	int i;

	for (i = 0; i < len; i++) {
		if (i != 0 && i % 32 == 0) printf("\n");
		if (i % 4 == 0) printf(" ");
		printf("%02x", (unsigned char)buf[i]);
	}
#if 0
	if (i % 32 != 0) printf("\n");
#endif

	return;
}