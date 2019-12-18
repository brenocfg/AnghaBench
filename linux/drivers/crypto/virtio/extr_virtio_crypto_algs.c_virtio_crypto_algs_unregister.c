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
typedef  int /*<<< orphan*/  uint32_t ;
struct virtio_crypto {int dummy; } ;
struct TYPE_3__ {int active_devs; int /*<<< orphan*/  algo; int /*<<< orphan*/  algonum; int /*<<< orphan*/  service; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  algs_lock ; 
 int /*<<< orphan*/  crypto_unregister_alg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  virtcrypto_algo_is_supported (struct virtio_crypto*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* virtio_crypto_algs ; 

void virtio_crypto_algs_unregister(struct virtio_crypto *vcrypto)
{
	int i = 0;

	mutex_lock(&algs_lock);

	for (i = 0; i < ARRAY_SIZE(virtio_crypto_algs); i++) {

		uint32_t service = virtio_crypto_algs[i].service;
		uint32_t algonum = virtio_crypto_algs[i].algonum;

		if (virtio_crypto_algs[i].active_devs == 0 ||
		    !virtcrypto_algo_is_supported(vcrypto, service, algonum))
			continue;

		if (virtio_crypto_algs[i].active_devs == 1)
			crypto_unregister_alg(&virtio_crypto_algs[i].algo);

		virtio_crypto_algs[i].active_devs--;
	}

	mutex_unlock(&algs_lock);
}