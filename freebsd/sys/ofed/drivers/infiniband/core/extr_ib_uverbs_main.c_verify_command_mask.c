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
typedef  int u64 ;
struct ib_device {int uverbs_cmd_mask; int uverbs_ex_cmd_mask; } ;
typedef  int __u32 ;

/* Variables and functions */
 int IB_USER_VERBS_CMD_OPEN_QP ; 

__attribute__((used)) static int verify_command_mask(struct ib_device *ib_dev, __u32 command)
{
	u64 mask;

	if (command <= IB_USER_VERBS_CMD_OPEN_QP)
		mask = ib_dev->uverbs_cmd_mask;
	else
		mask = ib_dev->uverbs_ex_cmd_mask;

	if (mask & ((u64)1 << command))
		return 0;

	return -1;
}