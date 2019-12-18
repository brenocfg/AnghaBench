#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ibv_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  guid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  ENOMEM ; 
 int ERR (int /*<<< orphan*/ ) ; 
 TYPE_1__* calloc (int,int) ; 
 int check_abi_version () ; 
 TYPE_1__* cma_dev_array ; 
 int cma_dev_cnt ; 
 int /*<<< orphan*/  fastlock_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fastlock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ibv_free_device_list (struct ibv_device**) ; 
 int /*<<< orphan*/  ibv_get_device_guid (struct ibv_device*) ; 
 struct ibv_device** ibv_get_device_list (int*) ; 
 int /*<<< orphan*/  idm_lock ; 
 int /*<<< orphan*/  mut ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ucma_set_af_ib_support () ; 

int ucma_init(void)
{
	struct ibv_device **dev_list = NULL;
	int i, ret, dev_cnt;

	/* Quick check without lock to see if we're already initialized */
	if (cma_dev_cnt)
		return 0;

	pthread_mutex_lock(&mut);
	if (cma_dev_cnt) {
		pthread_mutex_unlock(&mut);
		return 0;
	}

	fastlock_init(&idm_lock);
	ret = check_abi_version();
	if (ret)
		goto err1;

	dev_list = ibv_get_device_list(&dev_cnt);
	if (!dev_list) {
		ret = ERR(ENODEV);
		goto err1;
	}

	if (!dev_cnt) {
		ret = ERR(ENODEV);
		goto err2;
	}

	cma_dev_array = calloc(dev_cnt, sizeof(*cma_dev_array));
	if (!cma_dev_array) {
		ret = ERR(ENOMEM);
		goto err2;
	}

	for (i = 0; dev_list[i]; i++)
		cma_dev_array[i].guid = ibv_get_device_guid(dev_list[i]);

	cma_dev_cnt = dev_cnt;
	ucma_set_af_ib_support();
	pthread_mutex_unlock(&mut);
	ibv_free_device_list(dev_list);
	return 0;

err2:
	ibv_free_device_list(dev_list);
err1:
	fastlock_destroy(&idm_lock);
	pthread_mutex_unlock(&mut);
	return ret;
}