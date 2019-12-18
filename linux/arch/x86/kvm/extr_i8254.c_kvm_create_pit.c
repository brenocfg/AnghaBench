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
typedef  int u32 ;
struct pid {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  func; } ;
struct TYPE_4__ {int /*<<< orphan*/  irq_acked; scalar_t__ gsi; } ;
struct TYPE_6__ {int /*<<< orphan*/  function; } ;
struct kvm_kpit_state {TYPE_1__ irq_ack_notifier; TYPE_3__ timer; int /*<<< orphan*/  lock; } ;
struct kvm_pit {scalar_t__ irq_source_id; int /*<<< orphan*/  worker; int /*<<< orphan*/  dev; int /*<<< orphan*/  speaker_dev; TYPE_2__ mask_notifier; struct kvm_kpit_state pit_state; struct kvm* kvm; int /*<<< orphan*/  expired; } ;
struct kvm {int /*<<< orphan*/  slots_lock; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  GFP_KERNEL_ACCOUNT ; 
 int /*<<< orphan*/  HRTIMER_MODE_ABS ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KVM_PIO_BUS ; 
 int /*<<< orphan*/  KVM_PIT_BASE_ADDRESS ; 
 int KVM_PIT_MEM_LENGTH ; 
 int KVM_PIT_SPEAKER_DUMMY ; 
 int /*<<< orphan*/  KVM_SPEAKER_BASE_ADDRESS ; 
 int /*<<< orphan*/  current ; 
 struct pid* get_pid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hrtimer_init (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct kvm_pit*) ; 
 int /*<<< orphan*/  kthread_create_worker (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_destroy_worker (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_init_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_free_irq_source_id (struct kvm*,scalar_t__) ; 
 int kvm_io_bus_register_dev (struct kvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvm_io_bus_unregister_dev (struct kvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvm_iodevice_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvm_pit_ack_irq ; 
 int /*<<< orphan*/  kvm_pit_reset (struct kvm_pit*) ; 
 int /*<<< orphan*/  kvm_pit_set_reinject (struct kvm_pit*,int) ; 
 scalar_t__ kvm_request_irq_source_id (struct kvm*) ; 
 struct kvm_pit* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pid_vnr (struct pid*) ; 
 int /*<<< orphan*/  pit_dev_ops ; 
 int /*<<< orphan*/  pit_do_work ; 
 int /*<<< orphan*/  pit_mask_notifer ; 
 int /*<<< orphan*/  pit_timer_fn ; 
 int /*<<< orphan*/  put_pid (struct pid*) ; 
 int /*<<< orphan*/  speaker_dev_ops ; 
 int /*<<< orphan*/  task_tgid (int /*<<< orphan*/ ) ; 

struct kvm_pit *kvm_create_pit(struct kvm *kvm, u32 flags)
{
	struct kvm_pit *pit;
	struct kvm_kpit_state *pit_state;
	struct pid *pid;
	pid_t pid_nr;
	int ret;

	pit = kzalloc(sizeof(struct kvm_pit), GFP_KERNEL_ACCOUNT);
	if (!pit)
		return NULL;

	pit->irq_source_id = kvm_request_irq_source_id(kvm);
	if (pit->irq_source_id < 0)
		goto fail_request;

	mutex_init(&pit->pit_state.lock);

	pid = get_pid(task_tgid(current));
	pid_nr = pid_vnr(pid);
	put_pid(pid);

	pit->worker = kthread_create_worker(0, "kvm-pit/%d", pid_nr);
	if (IS_ERR(pit->worker))
		goto fail_kthread;

	kthread_init_work(&pit->expired, pit_do_work);

	pit->kvm = kvm;

	pit_state = &pit->pit_state;
	hrtimer_init(&pit_state->timer, CLOCK_MONOTONIC, HRTIMER_MODE_ABS);
	pit_state->timer.function = pit_timer_fn;

	pit_state->irq_ack_notifier.gsi = 0;
	pit_state->irq_ack_notifier.irq_acked = kvm_pit_ack_irq;
	pit->mask_notifier.func = pit_mask_notifer;

	kvm_pit_reset(pit);

	kvm_pit_set_reinject(pit, true);

	mutex_lock(&kvm->slots_lock);
	kvm_iodevice_init(&pit->dev, &pit_dev_ops);
	ret = kvm_io_bus_register_dev(kvm, KVM_PIO_BUS, KVM_PIT_BASE_ADDRESS,
				      KVM_PIT_MEM_LENGTH, &pit->dev);
	if (ret < 0)
		goto fail_register_pit;

	if (flags & KVM_PIT_SPEAKER_DUMMY) {
		kvm_iodevice_init(&pit->speaker_dev, &speaker_dev_ops);
		ret = kvm_io_bus_register_dev(kvm, KVM_PIO_BUS,
					      KVM_SPEAKER_BASE_ADDRESS, 4,
					      &pit->speaker_dev);
		if (ret < 0)
			goto fail_register_speaker;
	}
	mutex_unlock(&kvm->slots_lock);

	return pit;

fail_register_speaker:
	kvm_io_bus_unregister_dev(kvm, KVM_PIO_BUS, &pit->dev);
fail_register_pit:
	mutex_unlock(&kvm->slots_lock);
	kvm_pit_set_reinject(pit, false);
	kthread_destroy_worker(pit->worker);
fail_kthread:
	kvm_free_irq_source_id(kvm, pit->irq_source_id);
fail_request:
	kfree(pit);
	return NULL;
}