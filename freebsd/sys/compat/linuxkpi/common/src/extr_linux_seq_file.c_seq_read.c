#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct seq_file {TYPE_1__* op; } ;
struct linux_file {struct seq_file* private_data; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_2__ {int (* show ) (struct seq_file*,void*) ;void* (* start ) (struct seq_file*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 void* stub1 (struct seq_file*,int /*<<< orphan*/ *) ; 
 int stub2 (struct seq_file*,void*) ; 

ssize_t
seq_read(struct linux_file *f, char *ubuf, size_t size, off_t *ppos)
{
	struct seq_file *m = f->private_data;
	void *p;
	int rc;
	off_t pos = 0;

	p = m->op->start(m, &pos);
	rc = m->op->show(m, p);
	if (rc)
		return (rc);
	return (size);
}