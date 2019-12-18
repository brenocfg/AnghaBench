#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct seq_file {int dummy; } ;
struct TYPE_5__ {TYPE_1__* ops; int /*<<< orphan*/  fadump_enabled; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* fadump_region_show ) (TYPE_2__*,struct seq_file*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  fadump_mutex ; 
 TYPE_2__ fw_dump ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,struct seq_file*) ; 

__attribute__((used)) static int fadump_region_show(struct seq_file *m, void *private)
{
	if (!fw_dump.fadump_enabled)
		return 0;

	mutex_lock(&fadump_mutex);
	fw_dump.ops->fadump_region_show(&fw_dump, m);
	mutex_unlock(&fadump_mutex);
	return 0;
}