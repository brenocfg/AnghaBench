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
struct crypto_async_request {int /*<<< orphan*/  tfm; } ;
struct cryptd_queue {int /*<<< orphan*/  cpu_queue; } ;
struct cryptd_cpu_queue {int /*<<< orphan*/  work; int /*<<< orphan*/  queue; } ;
typedef  int /*<<< orphan*/  refcount_t ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  cryptd_wq ; 
 int crypto_enqueue_request (int /*<<< orphan*/ *,struct crypto_async_request*) ; 
 int /*<<< orphan*/ * crypto_tfm_ctx (int /*<<< orphan*/ ) ; 
 int get_cpu () ; 
 int /*<<< orphan*/  put_cpu () ; 
 int /*<<< orphan*/  queue_work_on (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_read (int /*<<< orphan*/ *) ; 
 struct cryptd_cpu_queue* this_cpu_ptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cryptd_enqueue_request(struct cryptd_queue *queue,
				  struct crypto_async_request *request)
{
	int cpu, err;
	struct cryptd_cpu_queue *cpu_queue;
	refcount_t *refcnt;

	cpu = get_cpu();
	cpu_queue = this_cpu_ptr(queue->cpu_queue);
	err = crypto_enqueue_request(&cpu_queue->queue, request);

	refcnt = crypto_tfm_ctx(request->tfm);

	if (err == -ENOSPC)
		goto out_put_cpu;

	queue_work_on(cpu, cryptd_wq, &cpu_queue->work);

	if (!refcount_read(refcnt))
		goto out_put_cpu;

	refcount_inc(refcnt);

out_put_cpu:
	put_cpu();

	return err;
}