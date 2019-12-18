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
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 

__attribute__((used)) static void dump_buf(void *buf, int size, int data_only, int offset)
{
	__be32 *p = buf;
	int i;

	for (i = 0; i < size; i += 16) {
		pr_debug("%03x: %08x %08x %08x %08x\n", offset, be32_to_cpu(p[0]),
			 be32_to_cpu(p[1]), be32_to_cpu(p[2]),
			 be32_to_cpu(p[3]));
		p += 4;
		offset += 16;
	}
	if (!data_only)
		pr_debug("\n");
}