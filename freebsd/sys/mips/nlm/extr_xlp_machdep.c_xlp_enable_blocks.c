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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  DFS_DEVICE_RSA ; 
 int /*<<< orphan*/  XLP_IO_SYS_OFFSET (int) ; 
 int XLP_MAX_NODES ; 
 int /*<<< orphan*/  nlm_dev_exists (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_get_sys_regbase (int) ; 
 int /*<<< orphan*/  nlm_sys_enable_block (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xlp_enable_blocks(void)
{
	uint64_t sysbase;
	int i;

	for (i = 0; i < XLP_MAX_NODES; i++) {
		if (!nlm_dev_exists(XLP_IO_SYS_OFFSET(i)))
			continue;
		sysbase = nlm_get_sys_regbase(i);
		nlm_sys_enable_block(sysbase, DFS_DEVICE_RSA);
	}
}