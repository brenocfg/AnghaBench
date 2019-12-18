#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * in; int /*<<< orphan*/  mutex; int /*<<< orphan*/  cond; int /*<<< orphan*/  thread_id; int /*<<< orphan*/  block_encoder; scalar_t__ progress_out; scalar_t__ progress_in; TYPE_2__* coder; int /*<<< orphan*/  const* allocator; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ worker_thread ;
struct TYPE_6__ {size_t threads_initialized; TYPE_1__* thr; int /*<<< orphan*/  block_size; TYPE_1__* threads; } ;
typedef  TYPE_2__ lzma_stream_coder ;
typedef  int /*<<< orphan*/  lzma_ret ;
typedef  int /*<<< orphan*/  lzma_allocator ;

/* Variables and functions */
 int /*<<< orphan*/  LZMA_MEM_ERROR ; 
 int /*<<< orphan*/  LZMA_NEXT_CODER_INIT ; 
 int /*<<< orphan*/  LZMA_OK ; 
 int /*<<< orphan*/  THR_IDLE ; 
 int /*<<< orphan*/ * lzma_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  lzma_free (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  mythread_cond_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ mythread_cond_init (int /*<<< orphan*/ *) ; 
 scalar_t__ mythread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  mythread_mutex_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ mythread_mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  worker_start ; 

__attribute__((used)) static lzma_ret
initialize_new_thread(lzma_stream_coder *coder,
		const lzma_allocator *allocator)
{
	worker_thread *thr = &coder->threads[coder->threads_initialized];

	thr->in = lzma_alloc(coder->block_size, allocator);
	if (thr->in == NULL)
		return LZMA_MEM_ERROR;

	if (mythread_mutex_init(&thr->mutex))
		goto error_mutex;

	if (mythread_cond_init(&thr->cond))
		goto error_cond;

	thr->state = THR_IDLE;
	thr->allocator = allocator;
	thr->coder = coder;
	thr->progress_in = 0;
	thr->progress_out = 0;
	thr->block_encoder = LZMA_NEXT_CODER_INIT;

	if (mythread_create(&thr->thread_id, &worker_start, thr))
		goto error_thread;

	++coder->threads_initialized;
	coder->thr = thr;

	return LZMA_OK;

error_thread:
	mythread_cond_destroy(&thr->cond);

error_cond:
	mythread_mutex_destroy(&thr->mutex);

error_mutex:
	lzma_free(thr->in, allocator);
	return LZMA_MEM_ERROR;
}