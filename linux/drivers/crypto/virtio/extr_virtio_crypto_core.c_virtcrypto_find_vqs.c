#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  char const vq_callback_t ;
typedef  char const virtqueue ;
struct virtio_crypto {int max_data_queues; char const* ctrl_vq; TYPE_1__* data_vq; TYPE_2__* vdev; } ;
struct device {int dummy; } ;
struct TYPE_4__ {struct device dev; } ;
struct TYPE_3__ {char* name; char const* vq; int /*<<< orphan*/  engine; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  crypto_engine_alloc_init (struct device*,int) ; 
 char** kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (char const**) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 char* virtcrypto_dataq_callback ; 
 int virtio_find_vqs (TYPE_2__*,int,char const**,char const**,char const**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int virtcrypto_find_vqs(struct virtio_crypto *vi)
{
	vq_callback_t **callbacks;
	struct virtqueue **vqs;
	int ret = -ENOMEM;
	int i, total_vqs;
	const char **names;
	struct device *dev = &vi->vdev->dev;

	/*
	 * We expect 1 data virtqueue, followed by
	 * possible N-1 data queues used in multiqueue mode,
	 * followed by control vq.
	 */
	total_vqs = vi->max_data_queues + 1;

	/* Allocate space for find_vqs parameters */
	vqs = kcalloc(total_vqs, sizeof(*vqs), GFP_KERNEL);
	if (!vqs)
		goto err_vq;
	callbacks = kcalloc(total_vqs, sizeof(*callbacks), GFP_KERNEL);
	if (!callbacks)
		goto err_callback;
	names = kcalloc(total_vqs, sizeof(*names), GFP_KERNEL);
	if (!names)
		goto err_names;

	/* Parameters for control virtqueue */
	callbacks[total_vqs - 1] = NULL;
	names[total_vqs - 1] = "controlq";

	/* Allocate/initialize parameters for data virtqueues */
	for (i = 0; i < vi->max_data_queues; i++) {
		callbacks[i] = virtcrypto_dataq_callback;
		snprintf(vi->data_vq[i].name, sizeof(vi->data_vq[i].name),
				"dataq.%d", i);
		names[i] = vi->data_vq[i].name;
	}

	ret = virtio_find_vqs(vi->vdev, total_vqs, vqs, callbacks, names, NULL);
	if (ret)
		goto err_find;

	vi->ctrl_vq = vqs[total_vqs - 1];

	for (i = 0; i < vi->max_data_queues; i++) {
		spin_lock_init(&vi->data_vq[i].lock);
		vi->data_vq[i].vq = vqs[i];
		/* Initialize crypto engine */
		vi->data_vq[i].engine = crypto_engine_alloc_init(dev, 1);
		if (!vi->data_vq[i].engine) {
			ret = -ENOMEM;
			goto err_engine;
		}
	}

	kfree(names);
	kfree(callbacks);
	kfree(vqs);

	return 0;

err_engine:
err_find:
	kfree(names);
err_names:
	kfree(callbacks);
err_callback:
	kfree(vqs);
err_vq:
	return ret;
}