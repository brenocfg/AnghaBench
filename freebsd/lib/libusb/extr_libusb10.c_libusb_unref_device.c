#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ refcnt; int /*<<< orphan*/  os_priv; int /*<<< orphan*/  ctx; } ;
typedef  TYPE_1__ libusb_device ;

/* Variables and functions */
 int /*<<< orphan*/  CTX_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CTX_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  libusb20_dev_free (int /*<<< orphan*/ ) ; 

void
libusb_unref_device(libusb_device *dev)
{
	if (dev == NULL)
		return;			/* be NULL safe */

	CTX_LOCK(dev->ctx);
	dev->refcnt--;
	CTX_UNLOCK(dev->ctx);

	if (dev->refcnt == 0) {
		libusb20_dev_free(dev->os_priv);
		free(dev);
	}
}