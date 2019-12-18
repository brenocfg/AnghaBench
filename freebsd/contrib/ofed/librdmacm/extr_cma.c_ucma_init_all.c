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
 int /*<<< orphan*/ * cma_dev_array ; 
 int cma_dev_cnt ; 
 int cma_init_cnt ; 
 int /*<<< orphan*/  mut ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int ucma_init () ; 
 int ucma_init_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ucma_init_all(void)
{
	int i, ret = 0;

	if (!cma_dev_cnt) {
		ret = ucma_init();
		if (ret)
			return ret;
	}

	if (cma_init_cnt == cma_dev_cnt)
		return 0;

	pthread_mutex_lock(&mut);
	for (i = 0; i < cma_dev_cnt; i++) {
		ret = ucma_init_device(&cma_dev_array[i]);
		if (ret)
			break;
	}
	pthread_mutex_unlock(&mut);
	return ret;
}