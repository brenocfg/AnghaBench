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
struct fiq_handler {struct fiq_handler* next; int /*<<< orphan*/  dev_id; scalar_t__ (* fiq_op ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct fiq_handler* current_fiq ; 
 int /*<<< orphan*/  dump_stack () ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void release_fiq(struct fiq_handler *f)
{
	if (current_fiq != f) {
		pr_err("%s FIQ trying to release %s FIQ\n",
		       f->name, current_fiq->name);
		dump_stack();
		return;
	}

	do
		current_fiq = current_fiq->next;
	while (current_fiq->fiq_op(current_fiq->dev_id, 0));
}