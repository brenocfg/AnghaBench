#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rdt_resource {unsigned int mon_scale; } ;
struct kernfs_open_file {TYPE_2__* kn; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_6__ {int x86_cache_size; } ;
struct TYPE_5__ {TYPE_1__* parent; } ;
struct TYPE_4__ {struct rdt_resource* priv; } ;

/* Variables and functions */
 int EINVAL ; 
 TYPE_3__ boot_cpu_data ; 
 int kstrtouint (char*,int /*<<< orphan*/ ,unsigned int*) ; 
 unsigned int resctrl_cqm_threshold ; 

__attribute__((used)) static ssize_t max_threshold_occ_write(struct kernfs_open_file *of,
				       char *buf, size_t nbytes, loff_t off)
{
	struct rdt_resource *r = of->kn->parent->priv;
	unsigned int bytes;
	int ret;

	ret = kstrtouint(buf, 0, &bytes);
	if (ret)
		return ret;

	if (bytes > (boot_cpu_data.x86_cache_size * 1024))
		return -EINVAL;

	resctrl_cqm_threshold = bytes / r->mon_scale;

	return nbytes;
}