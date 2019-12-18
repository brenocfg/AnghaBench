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

/* Variables and functions */
 int /*<<< orphan*/ * cpu_to_cwq ; 
 int /*<<< orphan*/ * cpu_to_mau ; 
 int /*<<< orphan*/  global_ref ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  n2_spu_hvapi_unregister () ; 
 int /*<<< orphan*/  queue_cache_destroy () ; 
 int /*<<< orphan*/  spu_lock ; 

__attribute__((used)) static void release_global_resources(void)
{
	mutex_lock(&spu_lock);
	if (!--global_ref) {
		kfree(cpu_to_cwq);
		cpu_to_cwq = NULL;

		kfree(cpu_to_mau);
		cpu_to_mau = NULL;

		queue_cache_destroy();
		n2_spu_hvapi_unregister();
	}
	mutex_unlock(&spu_lock);
}