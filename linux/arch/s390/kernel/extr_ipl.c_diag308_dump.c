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
 int /*<<< orphan*/  DIAG308_LOAD_NORMAL_DUMP ; 
 int /*<<< orphan*/  DIAG308_SET ; 
 int /*<<< orphan*/  USEC_PER_SEC ; 
 int diag308 (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  udelay_simple (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void diag308_dump(void *dump_block)
{
	diag308(DIAG308_SET, dump_block);
	while (1) {
		if (diag308(DIAG308_LOAD_NORMAL_DUMP, NULL) != 0x302)
			break;
		udelay_simple(USEC_PER_SEC);
	}
}