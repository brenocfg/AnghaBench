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
struct dentry {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_4__ {int /*<<< orphan*/  extra; int /*<<< orphan*/  user; int /*<<< orphan*/  kernel; int /*<<< orphan*/  unit_mask; int /*<<< orphan*/  count; int /*<<< orphan*/  event; int /*<<< orphan*/  enabled; } ;
struct TYPE_3__ {unsigned int num_virt_counters; } ;

/* Variables and functions */
 int /*<<< orphan*/  avail_to_resrv_perfctr_nmi_bit (int /*<<< orphan*/ ) ; 
 TYPE_2__* counter_config ; 
 TYPE_1__* model ; 
 int /*<<< orphan*/  op_x86_virt_to_phys (unsigned int) ; 
 int /*<<< orphan*/  oprofilefs_create_ulong (struct dentry*,char*,int /*<<< orphan*/ *) ; 
 struct dentry* oprofilefs_mkdir (struct dentry*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int) ; 

__attribute__((used)) static int nmi_create_files(struct dentry *root)
{
	unsigned int i;

	for (i = 0; i < model->num_virt_counters; ++i) {
		struct dentry *dir;
		char buf[4];

		/* quick little hack to _not_ expose a counter if it is not
		 * available for use.  This should protect userspace app.
		 * NOTE:  assumes 1:1 mapping here (that counters are organized
		 *        sequentially in their struct assignment).
		 */
		if (!avail_to_resrv_perfctr_nmi_bit(op_x86_virt_to_phys(i)))
			continue;

		snprintf(buf,  sizeof(buf), "%d", i);
		dir = oprofilefs_mkdir(root, buf);
		oprofilefs_create_ulong(dir, "enabled", &counter_config[i].enabled);
		oprofilefs_create_ulong(dir, "event", &counter_config[i].event);
		oprofilefs_create_ulong(dir, "count", &counter_config[i].count);
		oprofilefs_create_ulong(dir, "unit_mask", &counter_config[i].unit_mask);
		oprofilefs_create_ulong(dir, "kernel", &counter_config[i].kernel);
		oprofilefs_create_ulong(dir, "user", &counter_config[i].user);
		oprofilefs_create_ulong(dir, "extra", &counter_config[i].extra);
	}

	return 0;
}