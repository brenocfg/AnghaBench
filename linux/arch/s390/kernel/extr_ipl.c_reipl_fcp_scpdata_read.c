#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct kobject {int dummy; } ;
struct file {int dummy; } ;
struct bin_attribute {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_3__ {size_t scp_data_len; void* scp_data; } ;
struct TYPE_4__ {TYPE_1__ fcp; } ;

/* Variables and functions */
 int /*<<< orphan*/  memory_read_from_buffer (char*,size_t,int /*<<< orphan*/ *,void*,size_t) ; 
 TYPE_2__* reipl_block_fcp ; 

__attribute__((used)) static ssize_t reipl_fcp_scpdata_read(struct file *filp, struct kobject *kobj,
				      struct bin_attribute *attr,
				      char *buf, loff_t off, size_t count)
{
	size_t size = reipl_block_fcp->fcp.scp_data_len;
	void *scp_data = reipl_block_fcp->fcp.scp_data;

	return memory_read_from_buffer(buf, count, &off, scp_data, size);
}