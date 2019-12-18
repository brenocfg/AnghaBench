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
struct thread_info {int preempt_count; int cpu; struct task_struct* task; int /*<<< orphan*/  flags; } ;
struct task_struct {int /*<<< orphan*/  comm; int /*<<< orphan*/  sibling; int /*<<< orphan*/  children; struct task_struct* group_leader; struct task_struct* real_parent; struct task_struct* parent; int /*<<< orphan*/  tasks; int /*<<< orphan*/  cpus_mask; int /*<<< orphan*/  state; struct thread_info* stack; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KERNEL_STACK_SIZE ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  _TIF_MCA_INIT ; 
 int /*<<< orphan*/  cpumask_set_cpu (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct task_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char const*,int) ; 
 struct thread_info* task_thread_info (struct task_struct*) ; 

__attribute__((used)) static void
format_mca_init_stack(void *mca_data, unsigned long offset,
		const char *type, int cpu)
{
	struct task_struct *p = (struct task_struct *)((char *)mca_data + offset);
	struct thread_info *ti;
	memset(p, 0, KERNEL_STACK_SIZE);
	ti = task_thread_info(p);
	ti->flags = _TIF_MCA_INIT;
	ti->preempt_count = 1;
	ti->task = p;
	ti->cpu = cpu;
	p->stack = ti;
	p->state = TASK_UNINTERRUPTIBLE;
	cpumask_set_cpu(cpu, &p->cpus_mask);
	INIT_LIST_HEAD(&p->tasks);
	p->parent = p->real_parent = p->group_leader = p;
	INIT_LIST_HEAD(&p->children);
	INIT_LIST_HEAD(&p->sibling);
	strncpy(p->comm, type, sizeof(p->comm)-1);
}