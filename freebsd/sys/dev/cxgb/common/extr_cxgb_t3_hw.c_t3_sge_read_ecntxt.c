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
typedef  int /*<<< orphan*/  adapter_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  F_EGRESS ; 
 int t3_sge_read_context (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *) ; 

int t3_sge_read_ecntxt(adapter_t *adapter, unsigned int id, u32 data[4])
{
	if (id >= 65536)
		return -EINVAL;
	return t3_sge_read_context(F_EGRESS, adapter, id, data);
}