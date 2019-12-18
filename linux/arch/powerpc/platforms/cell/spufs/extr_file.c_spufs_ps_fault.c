#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_fault_t ;
struct vm_fault {unsigned long pgoff; int /*<<< orphan*/  address; TYPE_3__* vma; } ;
struct spu_context {scalar_t__ state; TYPE_4__* spu; int /*<<< orphan*/  run_wq; } ;
struct TYPE_11__ {TYPE_2__* mm; } ;
struct TYPE_10__ {unsigned long problem_phys; } ;
struct TYPE_9__ {TYPE_1__* vm_file; } ;
struct TYPE_8__ {int /*<<< orphan*/  mmap_sem; } ;
struct TYPE_7__ {struct spu_context* private_data; } ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 scalar_t__ SPU_STATE_RUNNABLE ; 
 scalar_t__ SPU_STATE_SAVED ; 
 int /*<<< orphan*/  VM_FAULT_NOPAGE ; 
 int /*<<< orphan*/  VM_FAULT_SIGBUS ; 
 TYPE_5__* current ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 scalar_t__ fatal_signal_pending (TYPE_5__*) ; 
 int /*<<< orphan*/  get_spu_context (struct spu_context*) ; 
 int /*<<< orphan*/  put_spu_context (struct spu_context*) ; 
 scalar_t__ spu_acquire (struct spu_context*) ; 
 int /*<<< orphan*/  spu_context_nospu_trace (int /*<<< orphan*/ ,struct spu_context*) ; 
 int /*<<< orphan*/  spu_context_trace (int /*<<< orphan*/ ,struct spu_context*,TYPE_4__*) ; 
 int /*<<< orphan*/  spu_release (struct spu_context*) ; 
 int /*<<< orphan*/  spufs_ps_fault__enter ; 
 int /*<<< orphan*/  spufs_ps_fault__insert ; 
 int /*<<< orphan*/  spufs_ps_fault__sleep ; 
 int /*<<< orphan*/  spufs_ps_fault__wake ; 
 int spufs_wait (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmf_insert_pfn (TYPE_3__*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static vm_fault_t spufs_ps_fault(struct vm_fault *vmf,
				    unsigned long ps_offs,
				    unsigned long ps_size)
{
	struct spu_context *ctx = vmf->vma->vm_file->private_data;
	unsigned long area, offset = vmf->pgoff << PAGE_SHIFT;
	int err = 0;
	vm_fault_t ret = VM_FAULT_NOPAGE;

	spu_context_nospu_trace(spufs_ps_fault__enter, ctx);

	if (offset >= ps_size)
		return VM_FAULT_SIGBUS;

	if (fatal_signal_pending(current))
		return VM_FAULT_SIGBUS;

	/*
	 * Because we release the mmap_sem, the context may be destroyed while
	 * we're in spu_wait. Grab an extra reference so it isn't destroyed
	 * in the meantime.
	 */
	get_spu_context(ctx);

	/*
	 * We have to wait for context to be loaded before we have
	 * pages to hand out to the user, but we don't want to wait
	 * with the mmap_sem held.
	 * It is possible to drop the mmap_sem here, but then we need
	 * to return VM_FAULT_NOPAGE because the mappings may have
	 * hanged.
	 */
	if (spu_acquire(ctx))
		goto refault;

	if (ctx->state == SPU_STATE_SAVED) {
		up_read(&current->mm->mmap_sem);
		spu_context_nospu_trace(spufs_ps_fault__sleep, ctx);
		err = spufs_wait(ctx->run_wq, ctx->state == SPU_STATE_RUNNABLE);
		spu_context_trace(spufs_ps_fault__wake, ctx, ctx->spu);
		down_read(&current->mm->mmap_sem);
	} else {
		area = ctx->spu->problem_phys + ps_offs;
		ret = vmf_insert_pfn(vmf->vma, vmf->address,
				(area + offset) >> PAGE_SHIFT);
		spu_context_trace(spufs_ps_fault__insert, ctx, ctx->spu);
	}

	if (!err)
		spu_release(ctx);

refault:
	put_spu_context(ctx);
	return ret;
}