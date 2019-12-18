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
struct iic_cdevpriv {int /*<<< orphan*/  lock; scalar_t__ started; TYPE_1__* sc; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IIC_UNKNOWN ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  M_IIC ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct iic_cdevpriv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iicbus_release_bus (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iicbus_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iicbus_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
iicdtor(void *data)
{
	device_t iicdev, parent;
	struct iic_cdevpriv *priv;

	priv = data;
	KASSERT(priv != NULL, ("iic cdevpriv should not be NULL!"));

	iicdev = priv->sc->sc_dev;
	parent = device_get_parent(iicdev);

	if (priv->started) {
		iicbus_stop(parent);
		iicbus_reset(parent, IIC_UNKNOWN, 0, NULL);
		iicbus_release_bus(parent, iicdev);
	}

	sx_destroy(&priv->lock);
	free(priv, M_IIC);
}