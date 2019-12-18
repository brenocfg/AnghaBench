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
struct crypto_engine {int /*<<< orphan*/  kworker; } ;

/* Variables and functions */
 int crypto_engine_stop (struct crypto_engine*) ; 
 int /*<<< orphan*/  kthread_destroy_worker (int /*<<< orphan*/ ) ; 

int crypto_engine_exit(struct crypto_engine *engine)
{
	int ret;

	ret = crypto_engine_stop(engine);
	if (ret)
		return ret;

	kthread_destroy_worker(engine->kworker);

	return 0;
}