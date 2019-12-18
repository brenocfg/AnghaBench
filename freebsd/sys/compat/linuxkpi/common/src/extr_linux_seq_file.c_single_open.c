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
struct seq_operations {int (* show ) (struct seq_file*,void*) ;int /*<<< orphan*/  stop; int /*<<< orphan*/  next; int /*<<< orphan*/  start; } ;
struct seq_file {void* private; } ;
struct linux_file {scalar_t__ private_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  M_LSEQ ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  free (struct seq_operations*,int /*<<< orphan*/ ) ; 
 struct seq_operations* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int seq_open (struct linux_file*,struct seq_operations*) ; 
 int /*<<< orphan*/  single_next ; 
 int /*<<< orphan*/  single_start ; 
 int /*<<< orphan*/  single_stop ; 

int
single_open(struct linux_file *f, int (*show)(struct seq_file *, void *), void *d)
{
	struct seq_operations *op;
	int rc = -ENOMEM;

	op = malloc(sizeof(*op), M_LSEQ, M_NOWAIT);
	if (op) {
		op->start = single_start;
		op->next = single_next;
		op->stop = single_stop;
		op->show = show;
		rc = seq_open(f, op);
		if (rc)
			free(op, M_LSEQ);
		else
			((struct seq_file *)f->private_data)->private = d;

	}
	return (rc);
}