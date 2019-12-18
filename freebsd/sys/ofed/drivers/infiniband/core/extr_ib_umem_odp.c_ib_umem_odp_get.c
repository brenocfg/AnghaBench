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
struct mm_struct {int dummy; } ;
struct ib_umem {TYPE_2__* odp_data; } ;
struct TYPE_4__ {int /*<<< orphan*/ * ops; int /*<<< orphan*/  hlist; } ;
struct ib_ucontext {scalar_t__ tgid; int odp_mrs_count; int /*<<< orphan*/  umem_rwsem; TYPE_1__ mn; int /*<<< orphan*/  notifier_count; int /*<<< orphan*/  no_private_counters; int /*<<< orphan*/  umem_tree; } ;
typedef  scalar_t__ pid_t ;
struct TYPE_5__ {int mn_counters_active; void* page_list; void* dma_list; int /*<<< orphan*/  no_private_counters; int /*<<< orphan*/  interval_tree; int /*<<< orphan*/  notifier_completion; int /*<<< orphan*/  umem_mutex; struct ib_umem* umem; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_HLIST_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  downgrade_write (int /*<<< orphan*/ *) ; 
 scalar_t__ get_pid (int /*<<< orphan*/ ) ; 
 struct mm_struct* get_task_mm (int /*<<< orphan*/ ) ; 
 scalar_t__ ib_umem_end (struct ib_umem*) ; 
 int /*<<< orphan*/  ib_umem_notifiers ; 
 int ib_umem_num_pages (struct ib_umem*) ; 
 scalar_t__ ib_umem_start (struct ib_umem*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 TYPE_2__* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmput (struct mm_struct*) ; 
 int mmu_notifier_register (TYPE_1__*,struct mm_struct*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  put_pid (scalar_t__) ; 
 int /*<<< orphan*/  rbt_ib_umem_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  task_pid_group_leader (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfree (void*) ; 
 void* vzalloc (int) ; 

int ib_umem_odp_get(struct ib_ucontext *context, struct ib_umem *umem)
{
	int ret_val;
	pid_t our_pid;
	struct mm_struct *mm = get_task_mm(current);

	if (!mm)
		return -EINVAL;

	/* Prevent creating ODP MRs in child processes */
	rcu_read_lock();
	our_pid = get_pid(task_pid_group_leader(current));
	rcu_read_unlock();
	put_pid(our_pid);
	if (context->tgid != our_pid) {
		ret_val = -EINVAL;
		goto out_mm;
	}

	umem->odp_data = kzalloc(sizeof(*umem->odp_data), GFP_KERNEL);
	if (!umem->odp_data) {
		ret_val = -ENOMEM;
		goto out_mm;
	}
	umem->odp_data->umem = umem;

	mutex_init(&umem->odp_data->umem_mutex);

	init_completion(&umem->odp_data->notifier_completion);

	umem->odp_data->page_list = vzalloc(ib_umem_num_pages(umem) *
					    sizeof(*umem->odp_data->page_list));
	if (!umem->odp_data->page_list) {
		ret_val = -ENOMEM;
		goto out_odp_data;
	}

	umem->odp_data->dma_list = vzalloc(ib_umem_num_pages(umem) *
					  sizeof(*umem->odp_data->dma_list));
	if (!umem->odp_data->dma_list) {
		ret_val = -ENOMEM;
		goto out_page_list;
	}

	/*
	 * When using MMU notifiers, we will get a
	 * notification before the "current" task (and MM) is
	 * destroyed. We use the umem_rwsem semaphore to synchronize.
	 */
	down_write(&context->umem_rwsem);
	context->odp_mrs_count++;
	if (likely(ib_umem_start(umem) != ib_umem_end(umem)))
		rbt_ib_umem_insert(&umem->odp_data->interval_tree,
				   &context->umem_tree);
	if (likely(!atomic_read(&context->notifier_count)) ||
	    context->odp_mrs_count == 1)
		umem->odp_data->mn_counters_active = true;
	else
		list_add(&umem->odp_data->no_private_counters,
			 &context->no_private_counters);
	downgrade_write(&context->umem_rwsem);

	if (context->odp_mrs_count == 1) {
		/*
		 * Note that at this point, no MMU notifier is running
		 * for this context!
		 */
		atomic_set(&context->notifier_count, 0);
		INIT_HLIST_NODE(&context->mn.hlist);
		context->mn.ops = &ib_umem_notifiers;
		/*
		 * Lock-dep detects a false positive for mmap_sem vs.
		 * umem_rwsem, due to not grasping downgrade_write correctly.
		 */
		ret_val = mmu_notifier_register(&context->mn, mm);
		if (ret_val) {
			pr_err("Failed to register mmu_notifier %d\n", ret_val);
			ret_val = -EBUSY;
			goto out_mutex;
		}
	}

	up_read(&context->umem_rwsem);

	/*
	 * Note that doing an mmput can cause a notifier for the relevant mm.
	 * If the notifier is called while we hold the umem_rwsem, this will
	 * cause a deadlock. Therefore, we release the reference only after we
	 * released the semaphore.
	 */
	mmput(mm);
	return 0;

out_mutex:
	up_read(&context->umem_rwsem);
	vfree(umem->odp_data->dma_list);
out_page_list:
	vfree(umem->odp_data->page_list);
out_odp_data:
	kfree(umem->odp_data);
out_mm:
	mmput(mm);
	return ret_val;
}