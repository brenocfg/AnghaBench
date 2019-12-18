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
#define  DUMP_TYPE_CCW 129 
#define  DUMP_TYPE_FCP 128 
 int /*<<< orphan*/  diag308_dump (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_block_ccw ; 
 int /*<<< orphan*/  dump_block_fcp ; 
 int dump_type ; 

__attribute__((used)) static void __dump_run(void *unused)
{
	switch (dump_type) {
	case DUMP_TYPE_CCW:
		diag308_dump(dump_block_ccw);
		break;
	case DUMP_TYPE_FCP:
		diag308_dump(dump_block_fcp);
		break;
	default:
		break;
	}
}