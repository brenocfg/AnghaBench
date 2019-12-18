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
 int /*<<< orphan*/  DIAG308_LOAD_CLEAR ; 
 int /*<<< orphan*/  DIAG308_SET ; 
#define  IPL_TYPE_CCW 132 
#define  IPL_TYPE_FCP 131 
#define  IPL_TYPE_FCP_DUMP 130 
#define  IPL_TYPE_NSS 129 
#define  IPL_TYPE_UNKNOWN 128 
 int /*<<< orphan*/  diag308 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disabled_wait () ; 
 int /*<<< orphan*/ * reipl_block_ccw ; 
 int /*<<< orphan*/ * reipl_block_fcp ; 
 int /*<<< orphan*/ * reipl_block_nss ; 
 int reipl_type ; 

__attribute__((used)) static void __reipl_run(void *unused)
{
	switch (reipl_type) {
	case IPL_TYPE_CCW:
		diag308(DIAG308_SET, reipl_block_ccw);
		diag308(DIAG308_LOAD_CLEAR, NULL);
		break;
	case IPL_TYPE_FCP:
		diag308(DIAG308_SET, reipl_block_fcp);
		diag308(DIAG308_LOAD_CLEAR, NULL);
		break;
	case IPL_TYPE_NSS:
		diag308(DIAG308_SET, reipl_block_nss);
		diag308(DIAG308_LOAD_CLEAR, NULL);
		break;
	case IPL_TYPE_UNKNOWN:
		diag308(DIAG308_LOAD_CLEAR, NULL);
		break;
	case IPL_TYPE_FCP_DUMP:
		break;
	}
	disabled_wait();
}