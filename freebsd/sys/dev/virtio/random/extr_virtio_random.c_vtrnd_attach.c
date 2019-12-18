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
struct vtrnd_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EEXIST ; 
 int /*<<< orphan*/  atomic_compare_exchange_strong_explicit (int /*<<< orphan*/ *,struct vtrnd_softc**,struct vtrnd_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vtrnd_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  g_vtrnd_softc ; 
 int /*<<< orphan*/  memory_order_acquire ; 
 int /*<<< orphan*/  memory_order_release ; 
 int /*<<< orphan*/  random_source_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  random_vtrnd ; 
 int /*<<< orphan*/  virtio_set_feature_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vtrnd_alloc_virtqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtrnd_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtrnd_feature_desc ; 
 int /*<<< orphan*/  vtrnd_negotiate_features (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vtrnd_attach(device_t dev)
{
	struct vtrnd_softc *sc, *exp;
	int error;

	sc = device_get_softc(dev);

	virtio_set_feature_desc(dev, vtrnd_feature_desc);
	vtrnd_negotiate_features(dev);

	error = vtrnd_alloc_virtqueue(dev);
	if (error) {
		device_printf(dev, "cannot allocate virtqueue\n");
		goto fail;
	}

	exp = NULL;
	if (!atomic_compare_exchange_strong_explicit(&g_vtrnd_softc, &exp, sc,
	    memory_order_release, memory_order_acquire)) {
		error = EEXIST;
		goto fail;
	}
	random_source_register(&random_vtrnd);

fail:
	if (error)
		vtrnd_detach(dev);

	return (error);
}