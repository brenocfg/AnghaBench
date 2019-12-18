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
typedef  int /*<<< orphan*/  u32 ;
struct ccp_dm_workarea {int dummy; } ;
struct ccp_cmd_queue {int dummy; } ;

/* Variables and functions */
 int ccp_copy_to_from_sb (struct ccp_cmd_queue*,struct ccp_dm_workarea*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ccp_copy_from_sb(struct ccp_cmd_queue *cmd_q,
			    struct ccp_dm_workarea *wa, u32 jobid, u32 sb,
			    u32 byte_swap)
{
	return ccp_copy_to_from_sb(cmd_q, wa, jobid, sb, byte_swap, true);
}