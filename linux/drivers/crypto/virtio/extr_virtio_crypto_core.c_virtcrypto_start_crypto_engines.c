#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct virtio_crypto {size_t max_data_queues; TYPE_1__* data_vq; } ;
typedef  size_t int32_t ;
struct TYPE_2__ {scalar_t__ engine; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_engine_exit (scalar_t__) ; 
 int crypto_engine_start (scalar_t__) ; 

__attribute__((used)) static int virtcrypto_start_crypto_engines(struct virtio_crypto *vcrypto)
{
	int32_t i;
	int ret;

	for (i = 0; i < vcrypto->max_data_queues; i++) {
		if (vcrypto->data_vq[i].engine) {
			ret = crypto_engine_start(vcrypto->data_vq[i].engine);
			if (ret)
				goto err;
		}
	}

	return 0;

err:
	while (--i >= 0)
		if (vcrypto->data_vq[i].engine)
			crypto_engine_exit(vcrypto->data_vq[i].engine);

	return ret;
}